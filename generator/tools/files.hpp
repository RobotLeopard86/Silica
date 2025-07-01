#pragma once

#include <string_view>
#include <vector>
#include <string>

class Files {
  public:
	Files();

#ifdef _WIN32
	std::string to_utf8(const wchar_t* str, size_t size);
	std::wstring from_utf8(const char* str, size_t size);
#endif

	const std::string root;
	static constexpr char deliminator = '/';

	std::string executable_name();
	void correct_path(std::string* path);

	//change path to a directory to paths to files inside
	void complete_files(std::vector<std::string>* paths);

	std::string cut_filename(std::string str);
	bool is_absolute(const std::string& path);
};
