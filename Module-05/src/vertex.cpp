#include "vertex.hpp"

namespace algo
{
	// VERTEX
	vertex::vertex() : _pi(), _d() {}
	vertex *&vertex::pi() { return (_pi); }
	float &vertex::d() { return (_d); }
	vertex *vertex::get_pi() const { return (_pi); }
	bool vertex::operator==(const vertex &rhs) const { return (this == &rhs); }
	bool vertex::operator!=(const vertex &rhs) const { return (!operator==(rhs)); }
	bool vertex::operator<(const vertex &rhs) const { return (this < &rhs); }

	// DELAY VERTEX
	delay_vertex::delay_vertex() : _delay() {}
	delay_vertex::delay_vertex(float delay) : _delay(delay) {}
	float delay_vertex::get_delay() const { return (_delay); }
	void delay_vertex::set_delay(float delay) { _delay = delay; }
}
