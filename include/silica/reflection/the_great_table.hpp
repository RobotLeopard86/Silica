#pragma once

#include "actions.hpp"
#include "silica/types/unknown.hpp"

namespace silica {

	///the main component of reflection system - big table with function pointers
	///each reflectable type has to have a record in the table
	struct TheGreatTable {
		static const inline std::vector<Actions>& data() {
			return data_guard();
		}

		static size_t record(Actions actions) {
			auto& data = data_guard();

			data.push_back(actions);
			return data.size() - 1;
		}

	  private:
		//static initialization fiasco guard to guarantee the first place for UnknownActions
		static std::vector<Actions>& data_guard() {
			//zero index for unknown type
			static std::vector<Actions> data = {Actions(&UnknownActions::reflect,//
				&UnknownActions::type_name,										 //
				&UnknownActions::type_size,										 //
				&UnknownActions::construct,										 //
				&UnknownActions::destroy,										 //
				&UnknownActions::copy,											 //
				&UnknownActions::move)};

			return data;
		}
	};

}
