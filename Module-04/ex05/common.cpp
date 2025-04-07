#include "common.hpp"

namespace ft
{
	int generate_int(const int min, const int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return (dist(gen));
	}

	std::string select_string(const std::vector<std::string>& strings)
	{
		return (strings[generate_int(0, static_cast<int>(strings.size()) - 1)]);
	}
}
