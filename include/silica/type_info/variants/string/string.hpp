#pragma once

#include <cstddef>

#include "c_string.hpp"
#include "silica/tools/sizeof.hpp"
#include "istring.hpp"
#include "std_basic_string.hpp"
#include "std_basic_string_view.hpp"

namespace silica {

	struct String final {
		String() = delete;

		template<typename T>
		String(std::basic_string<T>* str, bool is_const) {
			new(_mem) StdBasicString<T>(str, is_const);
		}

		template<typename T>
		String(std::basic_string_view<T>* str, bool is_const) {
			new(_mem) StdBasicStringView<T>(str);
		}

		template<typename T>
		String(const T** str, bool is_const) {
			new(_mem) CString<T>(str);
		}

		Expected<None> assign(Var var) {
			return impl()->assign(var);
		}

		void unsafe_assign(void* ptr) {
			impl()->unsafe_assign(ptr);
		}

		std::string_view get() const {
			return impl()->get();
		}

		Expected<None> set(std::string_view value) {
			return impl()->set(value);
		}

		Var var() const {
			return impl()->var();
		}

	  private:
		char _mem[Sizeof<CString<char>, StdBasicString<char>, StdBasicStringView<char>>::max()];

		inline const IString* impl() const {
			return reinterpret_cast<const IString*>(&_mem[0]);
		}

		inline IString* impl() {
			return reinterpret_cast<IString*>(&_mem[0]);
		}
	};

}
