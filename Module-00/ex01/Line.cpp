#include "Line.hpp"

Line::~Line() {}

Line::Line(const Vector2 &p1, const Vector2 &p2) : 
	_x_factor(p1.get_y() - p2.get_y()),
	_y_factor(p2.get_x() - p1.get_x()),
	_offset(p1.get_x() * p2.get_y() - p2.get_x() * p1.get_y())
{
	if (p1 == p2)
		throw std::invalid_argument("Can't create a line from identical points");
}

Line &Line::operator=(const Line &rhs)
{
	_x_factor = rhs._x_factor;
	_y_factor = rhs._y_factor;
	_offset = rhs._offset;
	return (*this);
}

Line::Line(const Line &copy) : _x_factor(copy._x_factor), _y_factor(copy._y_factor), _offset(copy._offset) {}

float Line::get_x_factor() const
{
	return (_x_factor);
}

float Line::get_y_factor() const
{
	return (_y_factor);
}

float Line::get_offset() const
{
	return (_offset);
}

// _x_factor * x + _y_factor * ? + _offset = 0
// _x_factor * ? = -(_y_factor * y + _offset)
// ? = -(_y_factor * y + _offset) / _x_factor
Vector2 Line::solve_for_x(float y) const
{
	if (std::fabs(_x_factor) < std::numeric_limits<float>::epsilon())
		throw std::logic_error("Can't find a point on a horizontal line only by its y-coordinate");
	return (Vector2(-(_y_factor * y + _offset) / _x_factor, y));
}

// _x_factor * x + _y_factor * ? + _offset = 0
// _y_factor * ? = -(_x_factor * x + _offset)
// ? = -(_x_factor * x + _offset) / _y_factor
Vector2 Line::solve_for_y(float x) const
{
	if (std::fabs(_y_factor) < std::numeric_limits<float>::epsilon())
		throw std::logic_error("Can't find a point on a vertical line only by its x-coordinate");
	return (Vector2(x, -(_x_factor * x + _offset) / _y_factor));
}
