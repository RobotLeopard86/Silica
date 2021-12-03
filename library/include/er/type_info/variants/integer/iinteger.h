#pragma once

#include <cstddef>
#include <cstdint>

#include "er/expected.h"
#include "er/variable/var.h"

namespace er {

struct IInteger {
  virtual Var var() const = 0;
  virtual size_t size() const = 0;
  virtual bool is_signed() const = 0;
  virtual int64_t as_signed() const = 0;
  virtual uint64_t as_unsigned() const = 0;
  virtual Expected<None> set_signed(int64_t value) = 0;
  virtual Expected<None> set_unsigned(uint64_t value) = 0;
  virtual std::string to_string() const = 0;
};

}  // namespace er