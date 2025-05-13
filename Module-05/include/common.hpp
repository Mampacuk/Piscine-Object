#pragma once

#include <cstddef>
#include <vector>

// a time unit corresponding to 1 minute
using time_unit = size_t;

namespace sim
{
	class node;
	class railroad;
	struct connection
	{
		node &u;
		railroad &r;
		node &v;
	};
	using path = std::vector<connection>;
}
