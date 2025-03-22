#pragma once

#include <memory>

#include "silica/type_info/variants/array/array.h"
#include "silica/type_info/variants/map/map.h"
#include "silica/type_info/variants/object/object.h"
#include "silica/variable/box.h"
#include "lexer_yaml.yy.h"

namespace silica {

	class TypeInfo;

	class ParserYaml : rf_yaml::LexerYaml {
	  public:
		ParserYaml(const char* input, size_t input_size);
		explicit ParserYaml(std::istream& stream);

		Expected<None> deserialize(TypeInfo* info);

	  private:
		Expected<None> parse(TypeInfo* info);
		Expected<None> parse_str(TypeInfo* info);
		Expected<None> parse_ind(TypeInfo* info);

		Expected<None> parse_seq(TypeInfo* info);
		Expected<None> parse_seq(TypeId nested_type, std::function<Expected<None>(size_t, Var)> add);
		Expected<None> parse_flow_seq(TypeId nested_type, std::function<Expected<None>(size_t, Var)> add);

		static inline Expected<None> add_to_array(Array& a, size_t i, Var var);

		Expected<None> parse_map(Map& map);
		Expected<None> parse_map(std::function<Expected<None>()> add);
		Expected<None> parse_flow_map(std::function<Expected<None>()> add);
		inline Expected<None> parse_flow_map(Map& map);
		Expected<None> parse_map_value(Map& map);

		inline Expected<None> add_to_obj(Object& obj);
		inline Expected<None> add_to_map(Map& map, TypeInfo* info_key, TypeInfo* info_value);

		static inline bool is_end(int token);
		static inline bool is_new_line(int token);
		static inline bool is_null(const std::string& word);

		inline Error error(const char* str);
		inline Error error_token(char token);
		inline Error error_match();

		static inline bool parse_bool(std::string& str);
		static inline int64_t parse_int(std::string_view str);
		static inline double parse_double(std::string_view str);

		inline void next();
		char _token;

		std::unordered_map<std::string, Box> _anchors;
	};

}//namespace silica

#undef __retry
