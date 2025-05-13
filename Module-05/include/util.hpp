#pragma once
#include "common.hpp"

#include <cstddef>
#include <string>

namespace util
{
	time_unit extract_mins(const std::string &time);
	std::string convert_mins(time_unit mins);
}
