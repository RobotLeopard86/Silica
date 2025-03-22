#pragma once

#include "silica/reflection/type_name.hpp"
#include "ipointer.hpp"

namespace silica {

	template<typename T>
	struct StdUniquePtr : IPointer {
		StdUniquePtr(std::unique_ptr<T>* value, bool is_const)
		  : _value(value), _is_const(is_const) {
		}

		Expected<None> assign(Var var) override {
			auto t = TypeId::get(_value);
			if(var.type() != t) {
				return Error(format("Cannot assign type: {} to {}",//
					reflection::type_name(var.type()),			   //
					reflection::type_name(t)));
			}

			_value = static_cast<std::unique_ptr<T>*>(const_cast<void*>(var.raw()));
			_is_const = var.is_const();
			return None();
		}

		void unsafe_assign(void* ptr) override {
			_value = static_cast<std::unique_ptr<T>*>(ptr);
			_is_const = false;
		}

		Var var() const override {
			return Var(_value, _is_const);
		}

		bool is_null() const override {
			return _value->get() == nullptr;
		}

		void init() override {
			*_value = std::make_unique<T>();
		}

		Expected<Var> get_nested() const override {
			if(*_value == nullptr) {
				return Error("Pointer is null");
			}
			return Var(_value->get(), std::is_const_v<T>);
		}

	  private:
		std::unique_ptr<T>* _value;
		bool _is_const;
	};

}//namespace silica