#include "math.hpp"

#include <cmath>

namespace math
{
	float normal_force(float mass /* kg */)
	{
		return (mass * gravitational_acceleration);  // Newtons
	}

	float friction_force(float friction_coefficient, float mass /* kg */)
	{
		return (friction_coefficient * normal_force(mass));
	}

	float acceleration_with_friction(float acceleration_force /* Newtons */,
									 float mass /* kg */,
									 float friction_coefficient)
	{
		return ((acceleration_force - friction_force(friction_coefficient, mass)) / mass);
	}
}
