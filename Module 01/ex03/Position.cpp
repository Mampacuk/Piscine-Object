#include "Position.hpp"

Position::Position() : x(), y(), z()
{
	std::cout << *this << " default-constructed" << std::endl;
}

Position::~Position()
{
	std::cout << *this << " destroyed" << std::endl;
}

Position::Position(int x, int y, int z) : x(x), y(y), z(z)
{
	std::cout << *this << " arg-constructed" << std::endl;
}

Position::Position(const Position &copy) : x(copy.x), y(copy.y), z(copy.z)
{
	std::cout << "Position copy-constructed from " << copy << std::endl;
}

Position &Position::operator=(const Position &rhs)
{
	std::cout << *this << " assigned to " << rhs << std::endl;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return (*this);
}

std::ostream &operator<<(std::ostream &o, const Position &p)
{
	o << "Position(x: " << p.x << ", y: " << p.y << ", z: " << p.z << ")";
	return (o);
}
