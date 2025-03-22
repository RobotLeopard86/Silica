#pragma once

#include <string_view>

#include "silica/error/error.h"
#include "silica/type_id.h"

using namespace er;

namespace er::sequence {

	///move error formating functionality outside sequence template classes
	class ErrHelper {
	  protected:
		static Error error(std::string_view message, TypeId type, TypeId nested_type);
	};

}//namespace er::sequence