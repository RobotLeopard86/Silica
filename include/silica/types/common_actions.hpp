#pragma once

#include <cstddef>

#include "silica/reflection/the_great_table.hpp"
#include "silica/tools/names.hpp"

namespace silica {

	template<typename T>
	struct CommonActions {
		static std::string_view type_name() {
			static auto name = Names<T>::get();
			return name;
		}

		static size_t type_size() {
			return sizeof(T);
		}

		static void construct(void* p) {
			new(p) T();
		}

		static void destroy(void* p) {
			static_cast<T*>(p)->~T();
		}

		static void nop(void* p) {
		}

		static void copy(void* to, const void* from) {
			*static_cast<T*>(to) = *static_cast<const T*>(from);
		}

		static void move(void* to, void* from) {
			*static_cast<T*>(to) = std::move(*static_cast<T*>(from));
		}
	};

}
