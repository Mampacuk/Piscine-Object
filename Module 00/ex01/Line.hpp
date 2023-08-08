#ifndef LINE_HPP
# define LINE_HPP

# include "Vector2.hpp"

# include <stdexcept>

class Line
{
    private:
        const float _x_factor;
        const float _y_factor;
        const float _offset;

        // deleted {
        Line();
        Line &operator=(const Line&);
        // } deleted
    public:
        ~Line();
        Line(const Vector2 &p1, const Vector2 &p2);
        Line(const Line &copy);
        Vector2 solve_for_x(float y) const;
        Vector2 solve_for_y(float x) const;
};

#endif
