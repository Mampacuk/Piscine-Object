#ifndef CIRCLE_HPP
# define CIRCLE_HPP

# include "shape.hpp"

# define _USE_MATH_DEFINES
# include <cmath>

class Circle : public Shape
{
	public:
		Circle() : _radius() {}
		Circle(const Circle &other) { *this = other; }
		Circle &operator=(const Circle &other) { _radius = other._radius; return (*this); }
		~Circle() {}
		Circle(const float radius) : _radius(radius) {}
		float area() const { return (M_PI * _radius * _radius); }
		float perimeter() const { return (2 * M_PI * _radius); }
	private:
		float _radius;
};

#endif
