#pragma once

#include "colors.hpp"

#include <string>
#include <iostream>

class [[silica::reflect("all")]] Car {
  public:
	Car(const std::string& owner, const std::string& brand, unsigned int year)
	  : owner(owner), brand(brand), year(year) {}

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