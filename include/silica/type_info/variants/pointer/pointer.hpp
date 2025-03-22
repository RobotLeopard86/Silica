#pragma once

#include "silica/tools/sizeof.hpp"
#include "ipointer.hpp"
#include "std_shared_ptr.hpp"
#include "std_unique_ptr.hpp"

namespace silica {

	struct Pointer {
		template<typename T>
		Pointer(std::shared_ptr<T>* value, bool is_const) {
			new(_mem) StdSharedPtr<T>(value, is_const);
		}

		template<typename T>
		Pointer(std::unique_ptr<T>* value, bool is_const) {
			new(_mem) StdUniquePtr<T>(value, is_const);
		}

		Expected<None> assign(Var var) {
			return impl()->assign(var);
		}

		void unsafe_assign(void* ptr) {
			impl()->unsafe_assign(ptr);
		}

		Var var() const {
			return impl()->var();
		}

		bool is_null() const {
			return impl()->is_null();
		}

		void init() {
			impl()->init();
		}

		Expected<Var> get_nested() const {
			return impl()->get_nested();
		}

	  private:
		char _mem[Sizeof<StdUniquePtr<int>, StdSharedPtr<int>>::max()];

		inline const IPointer* impl() const {
			return reinterpret_cast<const IPointer*>(&_mem[0]);
		}

		inline IPointer* impl() {
			return reinterpret_cast<IPointer*>(&_mem[0]);
		}
	};

}
