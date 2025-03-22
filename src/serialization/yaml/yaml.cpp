#include "silica/serialization/yaml.h"

#include <ostream>

#include "../writers/stream_writer.h"
#include "../writers/string_writer.h"
#include "silica/reflection/reflection.h"
#include "silica/types/all_types.h"
#include "parser_yaml.h"
#include "serializer.h"

using namespace er::serialization;

void yaml::serialize(std::string* str, Var var) {
	StringWriter string_w(str);
	auto info = reflection::reflect(var);

	serialize_recursive(&string_w, info, 0);
}

void yaml::serialize(std::ostream& stream, Var var) {
	StreamWriter stream_w(stream);
	auto info = reflection::reflect(var);

	serialize_recursive(&stream_w, info, 0);
}

Expected<None> yaml::deserialize(Var var, std::string_view str) {
	ParserYaml parser(str.data(), str.size());
	auto info = reflection::reflect(var);

	return parser.deserialize(&info);
}

Expected<None> yaml::deserialize(Var var, std::istream& stream) {
	ParserYaml parser(stream);
	auto info = reflection::reflect(var);

	return parser.deserialize(&info);
}