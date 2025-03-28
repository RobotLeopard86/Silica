#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

#include "iwriter.hpp"

namespace silica {

	struct VectorWriter final : IWriter {
		VectorWriter() = delete;

		explicit VectorWriter(std::vector<uint8_t>* vector)
		  : _vector(vector), _i(0) {
		}

		void write(const void* ptr, size_t bytes) override {
			_vector->resize(_vector->size() + bytes);
			std::memcpy(&(*_vector)[_i], ptr, bytes);
			_i += bytes;
		}

		void write(uint8_t ch) override {
			_vector->push_back(ch);
			_i += 1;
		}

		uint8_t peek() const override {
			return _vector->at(_vector->size() - 1);
		}

		void step_back(size_t bytes) override {
			_vector->resize(_vector->size() - bytes);
			_i -= bytes;
		}

	  private:
		std::vector<uint8_t>* _vector;
		size_t _i;
	};

}