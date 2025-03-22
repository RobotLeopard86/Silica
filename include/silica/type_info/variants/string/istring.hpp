#pragma once

#include <string_view>

#include "silica/expected.hpp"
#include "silica/variable/var.hpp"

namespace silica {

	struct IString {
		virtual ~IString() = default;

		virtual Expected<None> assign(Var var) = 0;
		virtual void unsafe_assign(void* ptr) = 0;
		virtual std::string_view get() const = 0;
		virtual Expected<None> set(std::string_view value) = 0;
		virtual Var var() const = 0;
	};

}//namespace silica
