#include "util.hpp"

#include "math.hpp"

#include <stdexcept>

namespace util
{
	time_unit extract_mins(const std::string &time)
	{
		const size_t hpos = time.find_first_of('h');
		if (hpos == std::string::npos)
			throw std::invalid_argument("Invalid time format: an 'h' must be present");
		if (hpos != time.find_last_of('h'))
			throw std::invalid_argument("Invalid time format: only one 'h' is allowed");
		if (hpos == time.size() - 1)
			throw std::invalid_argument("Invalid time format: no minutes specified");
		const std::string hours_str = time.substr(0, hpos);
		if (hours_str.empty())
			throw std::invalid_argument("Invalid time format: no hours specified");
		size_t end_index;
		const size_t hours = std::stoull(hours_str, &end_index);
		if (end_index != hours_str.size())
			throw std::invalid_argument("Invalid time format: bad hours string");
		const std::string minutes_str = time.substr(hpos + 1);
		const time_unit minutes = std::stoull(minutes_str, &end_index);
		if (end_index != minutes_str.size())
			throw std::invalid_argument("Invalid time format: bad minutes string");
		return (math::minutes_in_hour * hours + minutes);
	}

	std::string convert_mins(time_unit mins)
	{
		return ((mins / math::minutes_in_hour < 10 ? "0" : "") + std::to_string(mins / math::minutes_in_hour)
				+ "h" + (mins % math::minutes_in_hour < 10 ? "0" : "") + std::to_string(mins % math::minutes_in_hour));
	}
}
