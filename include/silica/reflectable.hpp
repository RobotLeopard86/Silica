#pragma once

#include <concepts>
#include <type_traits>

#include "silica/type_id.hpp"

namespace silica {
	template<typename T>
	concept Reflectable = std::is_enum_v<T> || (std::default_initializable<T> && requires(const T t) {
		{ t.SILICA__gettypeid() } -> std::same_as<TypeId>;
	});
}