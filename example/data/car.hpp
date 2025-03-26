#pragma once

#include "colors.hpp"

#include "silica/types/type_actions.hpp"

#include <string>
#include <iostream>

#define REFINISH_COST 8000

namespace silica {}

class [[silica::reflect("all")]] Car {
  public:
	std::string owner, brand;
	unsigned int year;
	[[silica::alias("insured")]] bool hasInsurance = false;
	[[silica::ignore]] bool hasSatRadio = false;

	int refinish(Color newColor) {
		color = newColor;
		return REFINISH_COST;
	}

	Color whatColorAmI() {
		return color;
	}

  private:
	Color color = Color::Green;

	friend struct silica::TypeActions<Car>;
};