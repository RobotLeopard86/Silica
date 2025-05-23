#include "templates.hpp"

#include "tools/files.hpp"
#include "parser/parser.hpp"
#include "tools/to_filename.hpp"

#include "CLI11.hpp"
#include "inja/inja.hpp"
#include "nlohmann/json.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include <filesystem>

#ifndef PROJECT_VER
#define PROJECT_VER "unknown"
#endif

#define VERBOSE_LOG(...) \
	if(verbose) std::cout << __VA_ARGS__ << std::endl;

#define clock std::chrono::steady_clock

int main(int argc, char* argv[]) {
	//Configure CLI
	CLI::App app("Silica reflection info generator", std::filesystem::path(argv[0]).filename().string());
	std::string compDbPath;
	app.add_option("-c", compDbPath, "Path to the compilation database directory")->check(CLI::ExistingDirectory)->required();
	std::string outDir;
	const auto outDirValidateFunc = [](const std::string& opt) {
		auto existDir = CLI::ExistingDirectory(opt);
		auto nonexist = CLI::NonexistentPath(opt);
		if(existDir.empty() || nonexist.empty()) {
			return "";
		}
		return "Provided path exists but is not a directory";
	};
	app.add_option("-o", outDir, "Path to the directory to output generated code to")->check(outDirValidateFunc)->required();
	std::vector<std::string> input;
	const auto inputValidateFunc = [](const std::string& opt) {
		auto existDir = CLI::ExistingDirectory(opt);
		auto existFile = CLI::ExistingFile(opt);
		if(existDir.empty() || existFile.empty()) {
			return "";
		}
		return "Provided path does not exist or is not a directory or file";
	};
	app.add_option("input", input, "Input header files to the generator")->check(inputValidateFunc)->required();
	std::string project;
	app.add_option("-p", project, "Name of the project")->transform([](const std::string& val) { return to_filename(val); })->required();
	bool verbose;
	app.add_flag("-V", verbose, "Print verbose output");
	app.set_version_flag("-v", []() { return PROJECT_VER; }, "Display version and exit");

	//Parse CLI arguments
	CLI11_PARSE(app, argc, argv);

	//Correct paths
	Files files;
	files.correct_path(&compDbPath);
	files.correct_path(&outDir);
	files.complete_files(&input);

	//If the output directory doesn't exist, we need to make it, or if it exists we need to empty it
	//We do this by deleting it if it exists, then remaking the directory
	std::filesystem::path out(outDir);
	if(std::filesystem::exists(out)) {
		std::filesystem::remove_all(out);
	}
	std::filesystem::create_directories(out);
	VERBOSE_LOG("Prepped output directory " << out)

	//Parse source files
	clock::time_point parseBegin = clock::now();
	Parser parser(compDbPath, out.string());
	std::unordered_map<std::string, nlohmann::json> parsed;
	for(std::string in : input) {
		//Parse this file
		std::vector<std::string> inAsVec(1);
		inAsVec[0] = in;
		auto maybeFR = parser.parse(inAsVec);
		if(!maybeFR.has_value()) {
			std::cerr << "Errors encountered while parsing source files!" << std::endl;
			return -1;
		}
		auto fileResults = maybeFR.value();

		//Correct origins
		for(auto& [_, json] : fileResults) {
			if(!json.contains("origin") || (json.contains("origin") && json["origin"].get<std::string>().compare("") == 0)) {
				//Calculate correct origin
				auto fs_path = std::filesystem::path(in.begin(), in.end());
				std::string rel = "../";
				rel += std::filesystem::relative(fs_path, out).string();
#if defined(_WIN32)
				std::replace(rel.begin(), rel.end(), '\\', '/');
#endif
				json["origin"] = rel;
			}
		}

		//Merge maps
		parsed.merge(fileResults);
	}
	clock::time_point parseEnd = clock::now();
	VERBOSE_LOG("Parsing source files completed in " << std::chrono::duration_cast<std::chrono::duration<float>>(parseEnd - parseBegin).count() << " seconds")

	//Create template objects
	inja::Environment inja;
	inja::Template headerTemplate = inja.parse(templates::Header);
	inja::Template enumTemplate = inja.parse(templates::Enum);
	inja::Template objectTemplate = inja.parse(templates::Object);
	VERBOSE_LOG("Loaded templates")

	//Write root files
	clock::time_point writeBegin = clock::now();
	std::ofstream rootHeader(out / (project + ".silica.hpp"));
	if(!rootHeader.is_open()) {
		std::cerr << "Failed to open root header file for writing!" << std::endl;
		return -1;
	}
	rootHeader << R"(
/* ---------------------------------------- *\
|                                            |
|   Silica-generated reflection info file.   |
|               DO NOT EDIT!                 |
|                                            |
\* ---------------------------------------- */

#pragma once

#include "silica/reflection/reflection.hpp"
#include "silica/types/all_types.hpp"

)";
	std::ofstream rootCpp(out / (project + ".silica.cpp"));
	if(!rootCpp.is_open()) {
		std::cerr << "Failed to open root implementation file for writing!" << std::endl;
		return -1;
	}
	rootCpp << R"(
/* ---------------------------------------- *\
|                                            |
|   Silica-generated reflection info file.   |
|               DO NOT EDIT!                 |
|                                            |
\* ---------------------------------------- */

#include ")"
			<< (project + ".silica.hpp") << "\"\n\n";

	//Create type reflection directory
	std::filesystem::path typesDir = out / "silica_types";
	std::filesystem::create_directories(typesDir);

	//Write file templates
	for(auto&& [object_name, json] : parsed) {
		//Generate filenames
		auto filenameUTF8 = to_filename(object_name);
		json["file_name"] = filenameUTF8;
		filenameUTF8 += ".silica";
#if defined(_WIN32)
		auto fileName = files.from_utf8(filenameUTF8.data(), filenameUTF8.size());

		auto hppFile = typesDir / (fileName + L".hpp");
		auto cppFile = typesDir / (fileName + L".cpp");
#else
		auto& fileName = filenameUTF8;
		auto hppFile = typesDir / (fileName + ".hpp");
		auto cppFile = typesDir / (fileName + ".cpp");
#endif

		//Open file streams
		std::ofstream hpp(hppFile);
		if(!hpp.is_open()) {
			std::cerr << "Failed to open type header file for writing!" << std::endl;
			return -1;
		}
		std::ofstream cpp(cppFile);
		if(!cpp.is_open()) {
			std::cerr << "Failed to open type implementation file for writing!" << std::endl;
			return -1;
		}

		//Write generation notes
		hpp << R"(
/* ---------------------------------------- *\
|                                            |
|   Silica-generated reflection info file.   |
|               DO NOT EDIT!                 |
|                                            |
\* ---------------------------------------- */

)";
		cpp << R"(
/* ---------------------------------------- *\
|                                            |
|   Silica-generated reflection info file.   |
|               DO NOT EDIT!                 |
|                                            |
\* ---------------------------------------- */

)";

		//Render templates
		inja.render_to(hpp, headerTemplate, json);
		hpp.close();
		VERBOSE_LOG("Generated " << hppFile);
		if(json["kind"].get<int>() == 0) {
			inja.render_to(cpp, objectTemplate, json);
		} else {
			inja.render_to(cpp, enumTemplate, json);
		}
		cpp.close();
		VERBOSE_LOG("Generated " << cppFile);

		//Add includes to root files
		const std::string includeStr = "#include \"silica_types/";
		rootHeader << includeStr << filenameUTF8 << ".hpp\"\n";
		rootCpp << includeStr << filenameUTF8 << ".cpp\"\n";
	}

	//Close root files
	rootHeader.close();
	VERBOSE_LOG("Generated " << out / (project + ".silica.hpp"));
	rootCpp.close();
	VERBOSE_LOG("Generated " << out / (project + ".silica.cpp"));
	clock::time_point writeEnd = clock::now();
	VERBOSE_LOG("File generation completed in " << std::chrono::duration_cast<std::chrono::duration<float>>(writeEnd - writeBegin).count() << " seconds")

	//Write done message
	VERBOSE_LOG("Done!")

	return 0;
}