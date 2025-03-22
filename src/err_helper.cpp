#include "silica/type_info/variants/sequence/err_helper.h"

#include "silica/error/error.h"
#include "silica/reflection/reflection.h"
#include "silica/tools/format.h"
#include "silica/types/all_types.h"

using namespace er;
using namespace er::sequence;

Error ErrHelper::error(std::string_view message, TypeId type, TypeId nested_type) {
	return Error(format(message,	//
		reflection::type_name(type),//
		reflection::type_name(nested_type)));
}
