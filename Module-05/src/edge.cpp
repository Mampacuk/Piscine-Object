#include "edge.hpp"

#include <cassert>

namespace algo
{
	// EDGE
	edge::edge(vertex &first, vertex &second) : _first(first), _second(second) {}
	vertex &edge::first() const { return (_first); }
	vertex &edge::second() const { return (_second); }
	bool edge::contains(const vertex &v) const
	{
		return (v == _first || v == _second);
	}
	vertex &edge::other(const vertex &v) const
	{
		return (v == _first ? _second : _first);
	}
	bool edge::operator==(const edge &rhs) const
	{
		return ((_first == rhs.first() && _second == rhs.second())
				|| (_first == rhs.second() && _second == rhs.first()));
	}
	bool edge::operator<(const edge &rhs) const
	{
		return (_first < rhs.first() || (!(rhs.first() < _first) && _second < rhs.second()));
	}

	// TIME-DEPENDENT EDGE
	time_dependent_edge::time_dependent_edge(vertex &first, vertex &second) : edge(first, second) {}

	void time_dependent_edge::book(booking time)
	{
		assert(time.first < time.second);
		if (available(time))
			_bookings.push_back(time);
	}

	bool time_dependent_edge::available(booking time) const
	{
		const auto [time_begin, time_end] = time;
		for (const auto &[booking_begin, booking_end] : _bookings)
			if (!(time_end < booking_begin || time_begin > booking_end))
				return (false);
		return (true);
	}
}
