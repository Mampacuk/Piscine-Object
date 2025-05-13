#pragma once

#include "constants.hpp"

#include <cstdlib>
#include <iostream>

namespace logging
{
	int error(const std::string &message);
	int info(const std::string &message);
}
