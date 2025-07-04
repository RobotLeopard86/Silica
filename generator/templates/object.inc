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
    auto* p = static_cast<{{name}}*>(value);

    static std::map<std::string_view, FieldDesc> fields {% if length(fields) != 0 %}{
      {% else %}{};{% endif -%}
      {% for item in fields -%}
        {"{{item.alias}}", FieldDesc(&{{name}}::{{item.name}}, Access::{{join(item.acc," | Access::")}})},
    {% if not loop.is_last %}  {% else %}};{% endif -%}
      {% endfor %}
    static std::map<std::string_view, MethodDesc> methods {% if length(methods) != 0 %}{
      {% else %}{};{% endif -%}
      {% for item in methods -%}
        {"{{item.alias}}", MethodDesc(&invoke_{{item.safe_name}}, Access::{{join(item.acc," | Access::")}})},
    {% if not loop.is_last %}  {% else %}};{% endif -%}
      {% endfor %}
    return Object(Var(p, is_const), &fields, &methods);
  }
{% for item in methods %}
  static Expected<None> invoke_{{item.safe_name}}(Var res, void* obj, const std::vector<Var>& args) {
    if (args.size() != {{length(item.params)}}) {
      return Error("Number of arguments is not the same as in the callable");
    }

    {% for type in item.params -%}
    if (args[{{loop.index}}].type() != TypeId::get<{{type}}>()) {
      return Error(silica::format("Argument type expected: {{type}}, received: {}", reflection::type_name(args[{{loop.index}}].type())));
    }
    const {{type}}& a{{loop.index}} = *static_cast<const {{type}}*>(args[{{loop.index}}].raw());

    {% endfor -%}

    {% if item.return != "void" -%}
    if (res.type() != TypeId::get<{{item.return}}>()) {
      return Error(silica::format("Return type expected: {{item.return}}, received: {}", reflection::type_name(res.type())));
    }
    *reinterpret_cast<{{item.return}}*>(res.raw_mut()) = //
    {% endif -%}
    std::invoke(&{{name}}::{{item.name}}{% if not ("kStatic" in item.acc) %}, static_cast<{{name}}*>(obj){% endif %}{% if length(item.params) != 0 %},{% else %});{% endif %}
      {% for i in range(length(item.params)) -%}
        a{{loop.index}}{% if not loop.is_last %},
      {% else %});{% endif -%}
      {% endfor %}
    return None();
  }
{% endfor -%}
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

TypeId {{name}}::SILICA__gettypeid() const {
	return TypeId::get<{{name}}>();
}

// clang-format on
)"