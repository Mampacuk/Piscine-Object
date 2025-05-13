#include "railroad.hpp"

#include "math.hpp"
#include "node.hpp"

namespace sim
{
	railroad::railroad(node &first, node &second, float length /* m */, float speed_limit /* m/s */)
	 		: algo::time_dependent_edge(first, second), _length(length / math::kilo), _speed_limit(math::m_s_to_km_min * speed_limit) {} 

	float railroad::get_length() const
	{
		return (_length);
	}

	float railroad::get_speed_limit() const
	{
		return (_speed_limit);
	}
}
