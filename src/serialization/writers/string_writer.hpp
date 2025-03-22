#pragma once

#include <cstddef>
#include <string>

#include "iwriter.hpp"

namespace silica {

	struct StringWriter final : IWriter {
		StringWriter() = delete;

		explicit StringWriter(std::string* string)
		  : _string(string) {
		}

		void write(const void* ptr, size_t bytes) override {
			_string->append(static_cast<const char*>(ptr), bytes);
		}

		void write(uint8_t ch) override {
			_string->push_back(ch);
		}

		uint8_t peek() const override {
			return _string->at(_string->size() - 1);
		}

		void step_back(size_t bytes) override {
			_string->resize(_string->size() - bytes);
		}

	  private:
		std::string* _string;
	};

}//namespace silica