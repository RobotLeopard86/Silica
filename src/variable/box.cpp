#include "silica/variable/box.hpp"

#include <cstdint>

#include "silica/alloc/alloc.hpp"
#include "silica/reflection/reflection.hpp"
#include "silica/types/all_types.hpp"

using namespace silica;

Box::Box(TypeId id, palloc_t* alloc)
  : _alloc(alloc) {
	_var = Var(_alloc->allocate(reflection::type_size(id)), id, false);
	reflection::construct(_var);
}

Box::Box(Box&& other) noexcept
  : _var(other._var), _alloc(other._alloc) {
	//prevent resource deletion
	other._var.dispose();
}

Box& Box::operator=(Box&& other) noexcept {
	_var = other._var;
	_alloc = other._alloc;

	//prevent resource deletion
	other._var.dispose();
	return *this;
}

Box::~Box() {
	reflection::destroy(_var);

	auto* p = reinterpret_cast<uint8_t*>(_var.raw_mut());
	auto size = reflection::type_size(_var.type());
	_alloc->deallocate(p, size);
}

Var Box::var() {
	return _var;
}

Box Box::clone() {
	Box new_one(_var.type());
	reflection::copy(new_one.var(), var());
	return new_one;
}
