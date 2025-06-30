#pragma once

#include <cstddef>
#include <istream>

#include "silica/expected.hpp"
#include "silica/variable/var.hpp"
#include "silica/reflectable.hpp"

namespace silica::serialization {

	struct binary {//NOLINT namespace like name
		template<Reflectable T>
		static Expected<T> from_vector(const std::vector<uint8_t>& vector) {
			T obj;

			auto exp = deserialize(Var(&obj), vector);
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
		static Expected<std::vector<uint8_t>> to_vector(const T* obj) {
			std::vector<uint8_t> result;
			serialize(&result, Var(obj));
			return result;
		}

		template<Reflectable T>
		static void to_stream(std::ostream& stream, const T* obj) {
			serialize(stream, Var(obj));
		}

		static void serialize(std::vector<uint8_t>* vector, Var var);
		static void serialize(std::ostream& stream, Var var);
		static Expected<None> deserialize(Var var, const std::vector<uint8_t>& vector);
		static Expected<None> deserialize(Var var, std::istream& stream);
	};

}