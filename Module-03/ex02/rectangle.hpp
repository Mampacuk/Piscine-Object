#ifndef RECTANGLE_HPP
# define RECTANGLE_HPP

# include "shape.hpp"

class Rectangle : public Shape
{
	public:
		Rectangle() : _first_side(), _second_side() {}
		Rectangle(const Rectangle &other) { *this = other; }
		Rectangle &operator=(const Rectangle &other) { _first_side = other._first_side; _second_side = other._second_side; return (*this); }
		~Rectangle() {}
		Rectangle(const float first_side, const float second_side) : _first_side(first_side), _second_side(second_side) {}
		float area() const { return (_first_side * _second_side); }
		float perimeter() const { return ((_first_side + _second_side) * 2); }
	private:
		float _first_side;
		float _second_side;
};

#endif
