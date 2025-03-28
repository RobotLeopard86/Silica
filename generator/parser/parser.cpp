#include "parser.hpp"

#include <cstddef>
#include <stdexcept>

#include "action.hpp"

//clang
#include "clang/Tooling/CompilationDatabase.h"
#include "llvm/ADT/StringRef.h"

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
	ActionFactory factory(&ctx);

	//handle macro attributes at first then
	//traverse AST, check attributes, build json objects and fill result field in context
	return (tool.run(&factory) == 0 ? std::make_optional(ctx.result) : std::nullopt);
}

Parser::~Parser() = default;
