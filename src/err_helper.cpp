#include "silica/type_info/variants/sequence/err_helper.hpp"

#include "silica/error/error.hpp"
#include "silica/reflection/reflection.hpp"
#include "silica/tools/format.hpp"
#include "silica/types/all_types.hpp"

using namespace silica;
using namespace silica::sequence;

Error ErrHelper::error(std::string_view message, TypeId type, TypeId nested_type) {
	return Error(silica::format(message,//
		reflection::type_name(type),	//
		reflection::type_name(nested_type)));
}
