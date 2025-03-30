#pragma once

#include <queue>

#include "../err_helper.hpp"
#include "silica/reflection/type_name.hpp"
#include "silica/variant/variant.hpp"
#include "iqueue.hpp"
#include "queue_iterator.hpp"

namespace silica {

	template<typename T>
	struct StdQueue : public IQueue, public sequence::ErrHelper {
		StdQueue() = delete;

		StdQueue(std::queue<T>* queue, bool is_const)
		  : _queue(queue),//
			_is_const(is_const) {
		}

		Expected<None> assign(Var var) override {
			auto t = TypeId::get(_queue);
			if(var.type() != t) {
				return Error(silica::format("Cannot assign type: {} to {}",//
					reflection::type_name(var.type()),					   //
					reflection::type_name(t)));
			}

			_queue = static_cast<std::queue<T>*>(const_cast<void*>(var.raw()));
			_is_const = var.is_const();
			return None();
		}

		void unsafe_assign(void* ptr) override {
			_queue = static_cast<std::queue<T>*>(ptr);
			_is_const = false;
		}

		Var own_var() const override {
			return Var(_queue, TypeId::get(_queue), _is_const);
		}

		TypeId nested_type() const override {
			return TypeId::get<T>();
		}

		void for_each(std::function<void(Var)> callback) const override {
			const auto nested_type = TypeId::get<T>();
			const auto end = QueueIterator<T>::end(_queue);

			for(auto it = QueueIterator<T>::begin(_queue); it != end; ++it) {
				callback(Var(&(*it), nested_type, true));
			}
		}

		void for_each(std::function<void(Var)> callback) override {
			const auto nested_type = TypeId::get<T>();
			const auto end = QueueIterator<T>::end(_queue);

			for(auto it = QueueIterator<T>::begin(_queue); it != end; ++it) {
				callback(Var(&(*it), nested_type, _is_const));
			}
		}

		void unsafe_for_each(std::function<void(void*)> callback) const override {
			const auto end = QueueIterator<T>::end(_queue);

			for(auto it = QueueIterator<T>::begin(_queue); it != end; ++it) {
				callback(&(*it));
			}
		}

		void clear() override {
			while(!_queue->empty()) {
				_queue->pop();
			}
		}

		size_t size() const override {
			return _queue->size();
		}

		Expected<None> push(Var value) override {
			auto nested_type = TypeId::get<T>();

			if(nested_type != value.type()) {
				return error("Trying to set with type: {} to queue<{}>",//
					value.type(), nested_type);
			}
			_queue->push(*static_cast<const T*>(value.raw()));
			return None();
		}

		void pop() override {
			_queue->pop();
		}

		Expected<Var> front() override {
			return Var(&_queue->front());
		};

		Expected<Var> back() override {
			return Var(&_queue->back());
		};

	  private:
		std::queue<T>* _queue;
		bool _is_const;
	};

}
