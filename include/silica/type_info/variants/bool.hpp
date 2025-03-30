#pragma once

#include <algorithm>
#include <cctype>
#include <string_view>

#include "silica/expected.hpp"
#include "silica/reflection/type_name.hpp"
#include "silica/tools/format.hpp"
#include "silica/type_id.hpp"
#include "silica/variable/var.hpp"

namespace silica {

	struct Bool {
		Bool(bool* value, bool is_const)
		  : _value(value), _is_const(is_const) {
		}

		Expected<None> assign(Var var) {
			auto t = TypeId::get<bool>();
			if(var.type() != t) {
				return Error(silica::format("Cannot assign type: {} to {}",//
					reflection::type_name(var.type()),					   //
					reflection::type_name(t)));
			}

			_value = const_cast<bool*>(static_cast<const bool*>(var.raw()));
			_is_const = var.is_const();
			return None();
		}

		void unsafe_assign(void* ptr) {
			_value = static_cast<bool*>(ptr);
			_is_const = false;
		}

		[[nodiscard]] bool get() const {
			return *_value;
		}

		Expected<None> set(bool value) {
			if(_is_const) {
				return Error("Trying to set const value");
			}
			*_value = value;
			return None();
		}

		Var var() {
			return Var(_value, _is_const);
		}

	  private:
		bool* _value;
		bool _is_const;
	};

}