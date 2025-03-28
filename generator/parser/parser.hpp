#pragma once

#include <string_view>
#include <vector>
#include <optional>

#include "context.hpp"

namespace clang {
	namespace tooling {
		class CompilationDatabase;
	}
}

class Parser {
  public:
	Parser(std::string_view compDBDir, std::string_view outputDir);
	~Parser();

	std::optional<std::unordered_map<std::string, nlohmann::json>> parse(const std::vector<std::string>& input);

  private:
	std::unique_ptr<clang::tooling::CompilationDatabase> compDB;
	Context ctx;
};
