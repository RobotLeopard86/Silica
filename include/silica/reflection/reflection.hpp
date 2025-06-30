#pragma once

#include "silica/reflectable.hpp"
#include "silica/type_id.hpp"
#include "silica/type_info/type_info.hpp"

namespace silica::reflection {

	TypeInfo reflect(Var variable);

	template<Reflectable T>
	TypeInfo reflect(T* pointer) {
		return reflection::reflect(Var(pointer));
	}

	template<Reflectable T>
	TypeInfo reflect(const T* pointer) {
		return reflection::reflect(Var(pointer));
	}

	std::string sprint(const TypeInfo& info);
	std::string sprint(Var var);

	template<Reflectable T>
	std::string sprint(const T* pointer) {
		return sprint(reflect(pointer));
	}

	void print(const TypeInfo& info);
	void print(Var var);

	template<Reflectable T>
	void print(const T* pointer) {
		print(reflect(pointer));
	}

	size_t type_size(TypeId id);

	void construct(Var variable);
	void destroy(Var variable);

	Expected<None> copy(Var to, Var from);

}
