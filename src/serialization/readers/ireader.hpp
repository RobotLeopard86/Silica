#pragma once

#include <cstddef>
#include <cstdint>

namespace silica {

	struct IReader {
		virtual void read(void* buff, size_t size) const = 0;
		virtual void peek(void* buff, size_t size) const = 0;
		virtual bool empty() const = 0;
	};

}