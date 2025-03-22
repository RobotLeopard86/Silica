#pragma once

#include "common_actions.h"
#include "silica/reflection/the_great_table.h"

namespace er {

	template<typename T>
	struct SequenceActions {
		static TypeInfo reflect(void* value, bool is_const) {
			return TypeInfo(Sequence(static_cast<T*>(value), is_const));
		}
	};

	template<typename T>
	typename std::enable_if_t<is_sequence_v<T>, TypeId>//
	TypeId::get(T* ptr) {
		static TypeId id(TheGreatTable::record(Actions(&SequenceActions<T>::reflect,//
			&CommonActions<T>::type_name,											//
			&CommonActions<T>::type_size,											//
			&CommonActions<T>::construct,											//
			&CommonActions<T>::destroy,												//
			&CommonActions<T>::copy,												//
			&CommonActions<T>::move)));
		return id;
	}

}//namespace er
