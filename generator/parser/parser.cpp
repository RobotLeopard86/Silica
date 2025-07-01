#include "parser.hpp"

#include <cstddef>
#include <sstream>
#include <stdexcept>

#include "action.hpp"

//clang
#include "clang/Tooling/ArgumentsAdjusters.h"
#include "clang/Tooling/CompilationDatabase.h"

namespace {
	std::unique_ptr<tooling::CompilationDatabase> load_compdb(std::string_view compdb_dir) {
		std::string err;

		auto source = StringRef(compdb_dir.data(), compdb_dir.size());
		auto compdb = tooling::CompilationDatabase::autoDetectFromDirectory(source, err);

		if(compdb == nullptr) {
			throw std::runtime_error("Cannot find compilation database, aborted");
		}
		return compdb;
	}
}

Parser::Parser(std::string_view compdb_dir,//
	std::string_view output_dir)		   //
  : compDB(load_compdb(compdb_dir)) {
	ctx.output_dir = output_dir;
}

std::optional<std::unordered_map<std::string, nlohmann::json>> Parser::parse(const std::vector<std::string>& input_files) {
	tooling::ClangTool tool(*compDB, input_files);
	tool.appendArgumentsAdjuster([this](const tooling::CommandLineArguments& args, StringRef) {
		tooling::CommandLineArguments adjArgs;
		adjArgs.push_back(args[0]);
		if(auto it = std::find_if(sysincludes.cbegin(), sysincludes.cend(), [](const std::string& si) {
#ifdef _WIN32
			   return si.find("c++\\v1") != std::string::npos;
#else
			   return si.find("c++/v1") != std::string::npos;
#endif
		   });
			it != sysincludes.cend()) {
			adjArgs.push_back(std::string("-isystem") + *it);
		}
		if(auto it = std::find_if(sysincludes.cbegin(), sysincludes.cend(), [](const std::string& si) {
#ifdef _WIN32
			   return si.find("lib\\clang") != std::string::npos;
#else
			   return si.find("lib/clang") != std::string::npos;
#endif
		   });
			it != sysincludes.cend()) {
			adjArgs.push_back(std::string("-isystem") + *it);
		}
		for(const std::string& include_dir : sysincludes) {
			adjArgs.push_back(std::string("-isystem") + include_dir);
		}
		for(int i = 1; i < args.size(); i++) {
			adjArgs.push_back(args[i]);
		}
		return adjArgs;
	});
	ActionFactory factory(&ctx);

	//handle macro attributes at first then
	//traverse AST, check attributes, build json objects and fill result field in context
	return (tool.run(&factory) == 0 ? std::make_optional(ctx.result) : std::nullopt);
}

Parser::~Parser() = default;
