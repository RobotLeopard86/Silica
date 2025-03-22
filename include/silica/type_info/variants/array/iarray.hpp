#pragma once

#include <functional>

#include "silica/variable/var.hpp"

namespace silica {

	struct IArray {
		virtual ~IArray() = default;

		virtual Expected<None> assign(Var var) = 0;
		virtual void unsafe_assign(void* ptr) = 0;
		virtual Var own_var() const = 0;
		virtual TypeId nested_type() const = 0;
		virtual void for_each(std::function<void(Var)> callback) const = 0;
		virtual void for_each(std::function<void(Var)> callback) = 0;
		virtual void unsafe_for_each(std::function<void(void*)> callback) const = 0;
		virtual size_t size() const = 0;
		virtual Expected<Var> front() = 0;
		virtual Expected<Var> back() = 0;
		virtual Expected<Var> at(size_t idx) = 0;
		virtual Expected<Var> operator[](size_t idx) = 0;
		virtual Expected<None> fill(Var filler) = 0;
	};

}//namespace silica
