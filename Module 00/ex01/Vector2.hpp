#ifndef VECTOR2_HPP
# define VECTOR2_HPP

# include <limits>

class Vector2
{
    private:
        float _x;
        float _y;
    public:
        Vector2();
        ~Vector2();
        Vector2(float x, float y);
        Vector2(const Vector2 &copy);
        Vector2 &operator=(const Vector2 &rhs);
        float get_x() const;
        float get_y() const;
};

bool operator==(const Vector2 &lhs, const Vector2 &rhs);
bool operator!=(const Vector2 &lhs, const Vector2 &rhs);
bool operator<(const Vector2 &lhs, const Vector2 &rhs);

#endif
