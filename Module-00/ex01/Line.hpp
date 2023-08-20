#ifndef LINE_HPP
# define LINE_HPP

# include "Vector2.hpp"

# include <cmath>
# include <stdexcept>

class Line
{
	private:
		float _x_factor;
		float _y_factor;
		float _offset;
		// deleted {
		Line();
		// } deleted
	public:
		~Line();
		Line(const Vector2 &p1, const Vector2 &p2);
		Line &operator=(const Line &rhs);
		Line(const Line &copy);
		float get_x_factor() const;
		float get_y_factor() const;
		float get_offset() const;
		Vector2 solve_for_x(float y) const;
		Vector2 solve_for_y(float x) const;
};

#endif
