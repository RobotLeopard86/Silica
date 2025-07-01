#pragma once

#include "colors.hpp"

#include "silica/type_id.hpp"
#include "silica/types/type_actions.hpp"

#include <string>

#define REFINISH_COST 8000

class [[silica::reflect("all")]] Car {
  public:
	std::string owner, brand;
	unsigned int year;
	[[silica::alias("insured")]] bool hasInsurance = false;
	[[silica::ignore]] bool hasSatRadio = false;

	virtual int refinish(Color newColor) {
		color = newColor;
		return REFINISH_COST;
	}

	Color whatColorAmI() {
		return color;
	}

	virtual silica::TypeId SILICA__gettypeid() const;

	virtual ~Car() {}

  private:
	Color color = Color::Green;

	friend struct silica::TypeActions<Car>;
};