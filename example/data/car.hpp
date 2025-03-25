#pragma once

#include "colors.hpp"

#include <string>
#include <iostream>

class [[silica::reflect("data", "func")]] Car {
  public:
	std::string owner, brand;
	unsigned int year;

	void refinish(Color newColor) {
		exterior = newColor;
	}

  private:
	Color exterior, interior;

	void enableSeatHeaters() {
		std::cout << "SECRET SEAT HEATERS ACTIVATED" << std::endl;
	}
};