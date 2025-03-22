#pragma once

#include <memory_resource>

#include "silica/alloc/alloc.h"
#include "silica/tools/sizeof.h"
#include "var.h"

namespace er {

	struct Box {
		Box(palloc_t* alloc = &default_alloc)
		  : _alloc(alloc) {};

		Box(const Box& other) = delete;
		Box& operator=(const Box& other) = delete;

		Box(Box&& other) noexcept;
		Box& operator=(Box&& other) noexcept;

		explicit Box(TypeId id, palloc_t* alloc = &default_alloc);
		~Box();

		Var var();
		Box clone();

	  private:
		Var _var;
		palloc_t* _alloc;

		//max size of stack memory for dynamic allocation optimization
		//static const size_t kMemSize = Sizeof<std::unordered_map<int, int>, std::map<int, int>>::max();
		//std::array<uint8_t, kMemSize> _buff;
	};

}//namespace er
