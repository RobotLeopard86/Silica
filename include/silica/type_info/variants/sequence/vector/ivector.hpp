#pragma once

#include "../isequence.h"

namespace er {

	struct IVector : public ISequence {
		~IVector() override = default;

		using ISequence::for_each;
		virtual void for_each(std::function<void(Var)> callback) = 0;
		virtual void pop() = 0;
		virtual Expected<Var> front() = 0;
		virtual Expected<Var> back() = 0;
		virtual Expected<Var> at(size_t idx) = 0;
		virtual Expected<Var> operator[](size_t idx) = 0;
	};

}//namespace er
