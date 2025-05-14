#pragma once

#include "algorithm.hpp"

namespace sim
{
	class railroad : public algo::time_dependent_edge
	{
		float _length;  // km
		float _speed_limit;  // km/min
	public:
		railroad(node &first, node &second, float length, float speed_limit /* m/s */);
		railroad() = delete;
		railroad(const railroad&) = default;
		railroad(railroad&&) = default;
		railroad &operator=(const railroad&) = delete;
		railroad &operator=(railroad&&) = delete;
		~railroad() = default;

		float get_length() const;
		float get_speed_limit() const;
	};
}
