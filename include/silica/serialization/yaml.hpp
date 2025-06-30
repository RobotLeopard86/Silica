#pragma once

#include <istream>
#include <string>

#include "silica/expected.hpp"
#include "silica/variable/var.hpp"
#include "silica/reflectable.hpp"

namespace silica::serialization {

	struct yaml {//NOLINT namespace like name
		template<Reflectable T>
		static Expected<T> from_string(std::string_view str) {
			T obj;

			auto exp = deserialize(Var(&obj), str);
			if(exp.is_error()) {
				return exp.error();
			}
			return obj;
		}

		template<Reflectable T>
		static Expected<T> from_stream(std::istream& stream) {
			T obj;

			auto exp = deserialize(Var(&obj), stream);
			if(exp.is_error()) {
				return exp.error();
			}
			return obj;
		}

		template<Reflectable T>
		static Expected<std::string> to_string(const T* obj) {
			std::string result;
			serialize(&result, Var(obj));
			return result;
		}

		template<Reflectable T>
		static void to_stream(std::ostream& stream, const T* obj) {
			serialize(stream, Var(obj));
		}

	  private:
		static void serialize(std::string* str, Var var);
		static void serialize(std::ostream& stream, Var var);
		static Expected<None> deserialize(Var var, std::string_view str);
		static Expected<None> deserialize(Var var, std::istream& stream);
	};

}