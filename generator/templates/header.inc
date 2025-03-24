R"(
#pragma once

#include "silica/type_id.hpp"
#include "silica/types/type_actions.hpp"

// injected
#include "{{origin}}"

namespace silica {

template <>
struct TypeActions<{{name}}>;

template <>
TypeId TypeId::get({{name}}* /*unused*/);

}
)"