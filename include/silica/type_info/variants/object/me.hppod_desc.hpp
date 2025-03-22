#pragma once

#include <type_traits>

#include "access.h"
#include "silica/tools/traits.h"
#include "silica/type_id.h"
#include "silica/variable/var.h"

namespace er {

	struct MethodDesc {
		MethodDesc(Expected<None> (*fn)(Var res, void* obj, const std::vector<Var>& args),//
			Access acc)
		  : _fn(fn), _acc(acc) {
		}

		Expected<None> invoke(Var res, void* obj, const std::vector<Var>& args) const {
			return _fn(res, obj, args);
		}

		bool is_const() const {
			return (_acc & Access::kConst) != Access::kNone;
		}

		bool is_static() const {
			return (_acc & Access::kStatic) != Access::kNone;
		}

		bool is_public() const {
			return (_acc & Access::kPublic) != Access::kNone;
		}

		bool is_protected() const {
			return (_acc & Access::kProtected) != Access::kNone;
		}

		bool is_private() const {
			return (_acc & Access::kPrivate) != Access::kNone;
		}

		Access access() const {
			return _acc;
		}

	  private:
		Expected<None> (*const _fn)(Var res, void* obj, const std::vector<Var>& args);
		const Access _acc;
	};

}//namespace er
