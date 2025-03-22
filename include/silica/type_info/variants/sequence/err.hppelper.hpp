#pragma once

#include <string_view>

#include "silica/error/error.hpp"
#include "silica/type_id.hpp"

using namespace silica;

namespace silica::sequence {

	///move error formating functionality outside sequence template classes
	class ErrHelper {
	  protected:
		static Error error(std::string_view message, TypeId type, TypeId nested_type);
	};

}//namespace silica::sequence