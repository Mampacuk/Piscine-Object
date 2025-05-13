#pragma once
#include "common.hpp"

#include <cstddef>

namespace math
{
	inline constexpr float kilo = 1000.f;
	inline constexpr float gravitational_acceleration = 9.80665f;  // m/s^2

	inline constexpr float m_s2_to_km_min2 = 3.6f;
	inline constexpr float m_s_to_km_min = 0.06f;

	inline constexpr float negligible_acceleration = 1e-6f;

	inline constexpr time_unit minutes_in_hour = 60;


	float normal_force(float mass /* kg */);  // Newtons

	float friction_force(float friction_coefficient, float mass /* kg */);  // Newtons

	float acceleration_with_friction(float acceleration_force, /* Newtons */
									 float mass, /* kg */
									 float friction_coefficient); // m/s^2
}
