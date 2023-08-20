#include "Vector2.hpp"

Vector2::Vector2() : _x(0.f), _y(0.f) {}

Vector2::~Vector2() {}

Vector2::Vector2(float x, float y) : _x(x), _y(y) {}

Vector2::Vector2(const Vector2 &copy) : _x(copy._x), _y(copy._y) {}

Vector2 &Vector2::operator=(const Vector2 &rhs)
{
	_x = rhs._x;
	_y = rhs._y;
	return (*this);
}

float Vector2::get_x() const
{
	return (_x);
}

float Vector2::get_y() const
{
	return (_y);
}

bool operator==(const Vector2 &lhs, const Vector2 &rhs)
{
	return (std::fabs(lhs.get_x() - rhs.get_x()) < std::numeric_limits<float>::epsilon()
			&& std::fabs(lhs.get_y() - rhs.get_y()) < std::numeric_limits<float>::epsilon());
}

bool operator!=(const Vector2 &lhs, const Vector2 &rhs)
{
	return (!(lhs == rhs));
}

bool operator<(const Vector2 &lhs, const Vector2 &rhs)
{
	return (lhs.get_x() < rhs.get_x() || (!(rhs.get_x() < lhs.get_x()) && lhs.get_y() < rhs.get_y()));
}
