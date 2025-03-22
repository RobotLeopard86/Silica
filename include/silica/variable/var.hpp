#pragma once

#include <type_traits>

#include "silica/expected.hpp"
#include "silica/type_id.hpp"

namespace silica {

	///The abstraction from type and const modifier
	///all types represented like a pointer + type id + const flag
	///the same representation for each type
	struct Var {
		Var();
		Var(void* value, TypeId type, bool is_const);

		template<typename T>
		explicit Var(const T* value)
		  : _value(const_cast<T*>(value)), _type(TypeId::get<T>()), _is_const(true) {
		}

		template<typename T>
		explicit Var(T* value, bool is_const = false)
		  : _value(value), _type(TypeId::get(value)), _is_const(is_const) {
		}

		void unsafe_assign(void* ptr);

		bool operator==(const Var& other) const;
		bool operator!=(const Var& other) const;

		void* raw_mut() const;
		const void* raw() const;

		TypeId type() const;

		bool is_const() const;

		void dispose();

		///runtime type check and cast
		template<typename T>
		Expected<T*> rt_cast() const {
			if(std::is_const_v<T> == false && is_const()) {
				return Error("The type under Var has const qualifier, cannot cast to mutable");
			}

			auto desired_type = TypeId::get<std::remove_const_t<T>>();

			if(desired_type != _type) {
				return error(_type, desired_type);
			}

			return static_cast<T*>(_value);
		}

	  private:
		void* _value;
		TypeId _type;
		bool _is_const;

		//include reflection header into .cpp file to avoid cyclic dependencies
		static Error error(TypeId type, TypeId desired_type);
	};

}//namespace silica
