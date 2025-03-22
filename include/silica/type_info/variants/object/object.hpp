#pragma once

#include <cstdint>
#include <iostream>
#include <map>
#include <utility>

#include "silica/expected.h"
#include "silica/reflection/type_name.h"
#include "silica/tools/format.h"
#include "silica/variable/var.h"
#include "fields.h"
#include "methods.h"

namespace er {

	///container of all field names matched to Var structs
	///just a registry of types and value pointers
	struct Object {
		Object(Var var,											//
			const std::map<std::string_view, FieldDesc>* fields,//
			const std::map<std::string_view, MethodDesc>* methods)
		  : _var(var),		//
			_fields(fields),//
			_methods(methods) {
		}

		Expected<None> assign(Var var) {
			if(var.type() != _var.type()) {
				return Error(format("Cannot assign type: {} to {}",//
					reflection::type_name(var.type()),			   //
					reflection::type_name(_var.type())));
			}
			_var = var;

			return None();
		}

		void unsafe_assign(void* ptr) {
			_var.unsafe_assign(ptr);
		}

		Expected<FieldInfo> get_field(std::string_view name) {
			auto it = _fields->find(name);

			if(it != _fields->end()) {
				return FieldInfo(_var.raw(), &it->second);
			}
			return Error(format("There is no field with name: '{}'", name));
		}

		Fields get_fields(Access access = Access::kPublic, bool include_readonly = false) const {
			return Fields(_var.raw(), _fields, access, include_readonly);
		}

		Expected<MethodInfo> get_method(std::string_view name) {
			auto it = _methods->find(name);

			if(it != _methods->end()) {

				if(_var.is_const()) {
					if(it->second.is_const()) {
						return MethodInfo(_var.raw(), &it->second);
					}
					return Error(format("Cannot call non const method '{}' on const object", name));
				}

				return MethodInfo(_var.raw_mut(), &it->second);
			}
			return Error(format("There is no method with name: '{}'", name));
		}

		Var var() {
			return _var;
		}

	  private:
		Var _var;
		const std::map<std::string_view, FieldDesc>* _fields;
		const std::map<std::string_view, MethodDesc>* _methods;
	};

}//namespace er
