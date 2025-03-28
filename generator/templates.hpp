#pragma once

#include <string>

namespace templates {
	const std::string Enum =
#include "templates/enum.inc"
		;
	const std::string Header =
#include "templates/header.inc"
		;
	const std::string Object =
#include "templates/object.inc"
		;
}