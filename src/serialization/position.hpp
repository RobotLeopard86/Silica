#pragma once

#include <cstddef>
#include <string>

#include "silica/tools/format.h"

namespace er {

	struct Position {
		size_t column = 0;
		size_t line_number = 0;

		std::string to_string() {
			return format("ln:{} col:{}", line_number + 1, column + 1);
		}
	};

}//namespace er
