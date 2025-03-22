#pragma once

#include "../isequence.h"

namespace er {

	struct ISet : public ISequence {
		~ISet() override = default;

		using ISequence::for_each;
		virtual Expected<None> remove(Var value) = 0;
		virtual bool contains(Var value) = 0;
	};

}//namespace er
