#pragma once

#include <list>

#include "../err_helper.hpp"
#include "silica/reflection/type_name.hpp"
#include "ilist.hpp"

namespace silica {

	template<typename T>
	struct StdList : public IList, public sequence::ErrHelper {
		StdList() = delete;

		StdList(std::list<T>* list, bool is_const)
		  : _list(list),//
			_is_const(is_const) {
		}

		Expected<None> assign(Var var) override {
			auto t = TypeId::get(_list);
			if(var.type() != t) {
				return Error(silica::format("Cannot assign type: {} to {}",//
					reflection::type_name(var.type()),					   //
					reflection::type_name(t)));
			}

			_list = static_cast<std::list<T>*>(const_cast<void*>(var.raw()));
			_is_const = var.is_const();
			return None();
		}

		void unsafe_assign(void* ptr) override {
			_list = static_cast<std::list<T>*>(ptr);
			_is_const = false;
		}

		Var own_var() const override {
			return Var(_list, TypeId::get(_list), _is_const);
		}

		TypeId nested_type() const override {
			return TypeId::get<T>();
		}

		void for_each(std::function<void(Var)> callback) const override {
			const auto nested_type = TypeId::get<T>();

			for(auto&& entry : *_list) {
				callback(Var(&entry, nested_type, true));
			}
		}

		void for_each(std::function<void(Var)> callback) override {
			const auto nested_type = TypeId::get<T>();

			for(auto&& entry : *_list) {
				callback(Var(&entry, nested_type, _is_const));
			}
		}

		void unsafe_for_each(std::function<void(void*)> callback) const override {
			for(auto&& entry : *_list) {
				callback(&entry);
			}
		}

		void clear() override {
			_list->clear();
		}

		size_t size() const override {
			return _list->size();
		}

		Expected<None> push(Var value) override {
			auto nested_type = TypeId::get<T>();

			if(nested_type != value.type()) {
				return error("Trying to set with type: {} to list<{}>",//
					value.type(), nested_type);
			}
			_list->push_back(*static_cast<const T*>(value.raw()));
			return None();
		}

		void pop() override {
			_list->pop_back();
		}

		void push_front(Var element) override {
			_list->push_front(*static_cast<const T*>(element.raw()));
		}

		void pop_front() override {
			_list->pop_front();
		}

		Expected<Var> front() override {
			if(_list->empty()) {
				return Error("The list is empty");
			}
			return Var(&_list->front(), TypeId::get<T>(), _is_const);
		};

		Expected<Var> back() override {
			if(_list->empty()) {
				return Error("The list is empty");
			}
			return Var(&_list->back(), TypeId::get<T>(), _is_const);
		};

	  private:
		std::list<T>* _list;
		bool _is_const;
	};

}
