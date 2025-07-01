#include "parser.hpp"

#include "clang/Tooling/CompilationDatabase.h"

#include <filesystem>
#include <fstream>
#include <set>
#include <iostream>
#include <regex>

#ifdef _WIN32
#include <windows.h>
#define popen _popen
#define pclose _pclose
#define pomode "rt"
#else
#include <unistd.h>
#define pomode "r"
#endif

using std::filesystem::path;

std::string runCommand(std::string cmd) {
#ifdef _WIN32
	std::stringstream cmdstr;
	cmdstr << "\"" << cmd << "\"";
	cmd = cmdstr.str();
#endif
	std::string output;
	FILE* pipe = popen(cmd.c_str(), pomode);
	if(!pipe) {
		std::cerr << "Failed to run command for system include detection: " << cmd << std::endl;
		exit(1);
	}
	std::vector<char> buffer(4096);
	while(true) {
		size_t bytesRead = fread(buffer.data(), 1, buffer.size(), pipe);
		if(bytesRead > 0) {
			output.append(buffer.data(), bytesRead);
		}
		if(bytesRead < buffer.size()) {
			if(feof(pipe)) break;
			if(ferror(pipe)) {
				std::cerr << "Error reading from compiler pipe" << std::endl;
				break;
			}
		}
	}
	pclose(pipe);
	return output;
}

//whitespace trimming helper
inline std::string trim(const std::string& s) {
	size_t start = s.find_first_not_of(" \t\r\n");
	size_t end = s.find_last_not_of(" \t\r\n");
	if(start == std::string::npos || end == std::string::npos) return "";
	return s.substr(start, end - start + 1);
}

std::set<std::string> gccLikeIncludeParser(const std::string& compiler_output) {
	std::set<std::string> includes;
	bool include_section = false;
	std::istringstream iss(compiler_output);
	std::string line;

	//Read through the lines until we get the system include search path, then take them all until we get to the end of that
	while(std::getline(iss, line)) {
		if(line.find("#include <...> search starts here:") != std::string::npos) {
			include_section = true;
			continue;
		}
		if(line.find("End of search list.") != std::string::npos) break;
		if(include_section) {
			//Remove whitespace and framework directory indicator
			auto trimmed = trim(line);
			if(auto pos = trimmed.find(" (framework directory)"); pos != std::string::npos) {
				trimmed = trimmed.substr(0, pos);
			}
			if(!trimmed.empty()) {
				includes.insert(trimmed);
			}
		}
	}
	return includes;
}

std::set<std::string> msvcIncludeParser(const std::string& compiler_output) {
	std::set<std::string> includes;

	//I love regexes /s
	std::regex include_line(R"(Note: including file:\s*(.+))", std::regex_constants::icase);
	std::smatch match;
	std::istringstream iss(compiler_output);
	std::string line;

	//Read through the lines and if it's one that is the compiler informing us of an include, take the filepath part, steal the directory, and add it to the set
	//A directory will be eliminated if it isn't unique (there could be duplicates due to extra backslashes, but the later canonization step fixes that)
	while(std::getline(iss, line)) {
		if(std::regex_search(line, match, include_line)) {
			path p(match[1].str());
			includes.insert(p.parent_path().string());
		}
	}
	return includes;
}

void Parser::find_sys_includes(const std::string& sample, const std::string& fallback_compiler, bool fallback_msvc) {
	std::string compiler = compDB->getCompileCommands(sample)[0].CommandLine[0];
	enum class CompilerType {
		GCCLike,
		MSVC,
		Bad
	} ctp = CompilerType::Bad;

	std::string lower = compiler;
	for(char& c : lower) c = (char)tolower(c);

#ifdef _WIN32
	//MSVC check
	if(lower.find("++") == std::string::npos && (lower.find("cl.exe") != std::string::npos || lower.find("cl") == 0)) ctp = CompilerType::MSVC;
#endif

	//GCC/Clang check
	if(lower.find("clang") != std::string::npos || lower.find("gcc") != std::string::npos) ctp = CompilerType::GCCLike;

	//Fallback
	if(ctp == CompilerType::Bad) {
		compiler = fallback_compiler;
		ctp = fallback_msvc ? CompilerType::MSVC : CompilerType::GCCLike;
	}

	std::set<std::string> includes;
	if(ctp == CompilerType::GCCLike) {
		//Empty file to feed in
		path empty_file = std::filesystem::temp_directory_path() / "_silicasysincchk.cpp";
		{
			std::ofstream ofstr(empty_file);
			ofstr.close();
		}

		//Run compiler
		std::string cmd = "\"" + compiler + "\" -E -xc++ -v \"" + empty_file.string() + "\" 2>&1";
		std::string output = runCommand(cmd);
		std::filesystem::remove(empty_file);

		//Parse includes
		includes = gccLikeIncludeParser(output);
	} else if(ctp == CompilerType::MSVC) {
#ifdef _WIN32
		//Dummy source (should detect all header paths we might need)
		const char* msvc_dummy_src = R"cpp(
        #include <stdio.h>
        #include <type_traits>
        #include <Windows.h>
        #include <asyncinfo.h>
        #include <winrt/base.h>
        #include <atlbase.h>
        )cpp";

		//Dummy file to feed in
		path dummy_file = std::filesystem::temp_directory_path() / "_silicasysincchk.cpp";
		{
			std::ofstream ofstr(dummy_file);
			ofstr << msvc_dummy_src;
			ofstr.close();
		}

		//Run compiler
		std::string cmd = "\"" + compiler + "\" /nologo /showIncludes /P /c \"" + dummy_file.string() + "\" 2>&1";
		std::string output = runCommand(cmd);
		std::filesystem::remove(dummy_file);

		//Parse includes
		includes = msvcIncludeParser(output);
#else
		std::cerr << "Cannot use MSVC for system include parsing on a non-Windows system!" << std::endl;
		exit(1);
#endif
	}

	//Canonize includes
	sysincludes.clear();
	for(const auto& inc : includes) {
		std::filesystem::path incp(inc);
		sysincludes.insert(std::filesystem::canonical(incp).string());
	}
}