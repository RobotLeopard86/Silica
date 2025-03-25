#pragma once

#include "colors.hpp"

#include <string>
#include <iostream>

#define REFINISH_COST 8000

class [[silica::reflect("data", "func")]] Car {
  public:
	std::string owner, brand;
	unsigned int year;
	[[silica::alias("insured")]] bool hasInsurance;
	[[silica::ignore]] bool hasSatRadio;

	int refinish(Color newColor) {
		finish = newColor;
		return REFINISH_COST;
	}

  private:
	Color finish;
};