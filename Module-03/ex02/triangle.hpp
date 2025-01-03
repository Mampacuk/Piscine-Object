#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "shape.hpp"

# include <cmath>

class Triangle : public Shape
{
	public:
		Triangle() : _first_side(), _second_side(), _third_side() {}
		Triangle(const Triangle &other) { *this = other; }
		Triangle &operator=(const Triangle &other) { _first_side = other._first_side; _second_side = other._second_side; _third_side = other._third_side; return (*this); }
		~Triangle() {}
		Triangle(const float first_side, const float second_side, const float third_side) : _first_side(first_side), _second_side(second_side), _third_side(third_side) {}
		float perimeter() const { return (_first_side + _second_side + _third_side); }
		float area() const
		{
			const float s = perimeter() / 2; // semi-perimeter, for Heron's formula
			return (std::sqrt(s * (s - _first_side ) * (s - _second_side) * (s - _third_side)));
		}
	private:
		float _first_side;
		float _second_side;
		float _third_side;
};

#endif
