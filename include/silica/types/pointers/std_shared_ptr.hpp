#pragma once

#include <memory>
#include <stdexcept>

#include "silica/reflection/the_great_table.hpp"
#include "silica/type_info/type_info.hpp"
#include "silica/type_info/variants/pointer/std_shared_ptr.hpp"
#include "silica/types/common_actions.hpp"
#include "silica/types/type_actions.hpp"

namespace silica {

	template<typename T>
	struct TypeActions<std::shared_ptr<T>> {

		static TypeInfo reflect(void* value, bool is_const) {
			return {Pointer(static_cast<std::shared_ptr<T>*>(value), is_const)};
		}
	};

	template<typename T>
	TypeId TypeId::get(std::shared_ptr<T>* /*unused*/) {
		static TypeId id(TheGreatTable::record(Actions(&TypeActions<std::shared_ptr<T>>::reflect,//
			&CommonActions<std::shared_ptr<T>>::type_name,										 //
			&CommonActions<std::shared_ptr<T>>::type_size,										 //
			&CommonActions<std::shared_ptr<T>>::construct,										 //
			&CommonActions<std::shared_ptr<T>>::destroy,										 //
			&CommonActions<std::shared_ptr<T>>::copy,											 //
			&CommonActions<std::shared_ptr<T>>::move)));
		return id;
	}

}//namespace silica
