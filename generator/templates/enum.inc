R"(
#include "{{file_name}}.silica.hpp"

// clang-format off
#include "silica/reflection/the_great_table.hpp"
#include "silica/types/common_actions.hpp"
#include "silica/types/type_actions.hpp"

namespace silica {

template <>
struct TypeActions<{{name}}> {
  static TypeInfo reflect(void* value, bool is_const) {

    static constexpr ConstexprMap<{{name}}, {{length(constants)}}> constants {% if length(constants) != 0 %}{{"{{{"}}
      {% else %}{};{% endif -%}
      {% for item in constants -%}
      {{"{"}}{{name}}::{{item.name}}, "{{item.alias}}"},
    {% if not loop.is_last %}  {% else %}}}};{% endif -%}
      {% endfor %}
    return Enum(static_cast<{{name}}*>(value), is_const, constants);
  }
};

template <>
TypeId TypeId::get({{name}}* /*unused*/) {
  static TypeId id(TheGreatTable::record(Actions(&TypeActions<{{name}}>::reflect,      //
                                                 &CommonActions<{{name}}>::type_name,  //
                                                 &CommonActions<{{name}}>::type_size,  //
                                                 &CommonActions<{{name}}>::construct,  //
                                                 &CommonActions<{{name}}>::destroy,    //
                                                 &CommonActions<{{name}}>::copy,       //
                                                 &CommonActions<{{name}}>::move)));
  return id;
}

}

// clang-format on
)"