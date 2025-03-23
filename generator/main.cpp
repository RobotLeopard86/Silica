#include "templates.hpp"

#include "CLI/CLI.hpp"

#include <string>
#include <vector>

int main(int argc, char* argv[]) {
	//Configure CLI
	CLI::App app("Silica reflection info generator", std::filesystem::path(argv[0]).filename());
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
	app.add_option("-i", input, "Input header files to the generator")->check(CLI::ExistingFile)->expected(1)->required();

	//Parse CLI arguments
	CLI11_PARSE(app, argc, argv);

	return 0;
}