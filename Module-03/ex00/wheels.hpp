#ifndef WHEELS_HPP
# define WHEELS_HPP

# include <iostream>

class Wheels
{
public:
	Wheels() : _angle(0.f) {}

	Wheels(const Wheels &other)
	{
		*this = other;
	}

	Wheels &operator=(const Wheels &other)
	{
		_angle = other._angle;
		return (*this);
	}

	~Wheels() {}

	void turn(const float angle)
	{
		const float old_angle = _angle;
		_angle += angle;
		std::cout << "Wheels turned from " << old_angle << " to " << _angle << std::endl;
	}

	void straighten()
	{
		_angle = 0.f;
		std::cout << "Wheels straightened" << std::endl;
	}

private:
	float _angle;
};

#endif
