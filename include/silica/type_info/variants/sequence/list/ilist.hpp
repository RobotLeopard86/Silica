#pragma once

#include "../isequence.hpp"

namespace silica {

	struct IList : public ISequence {
		~IList() override = default;

		using ISequence::for_each;
		virtual void for_each(std::function<void(Var)> callback) = 0;
		virtual void pop() = 0;
		virtual void push_front(Var value) = 0;
		virtual void pop_front() = 0;
		virtual Expected<Var> front() = 0;
		virtual Expected<Var> back() = 0;
	};

}
