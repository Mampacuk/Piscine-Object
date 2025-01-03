#ifndef BRAKES_HPP
# define BRAKES_HPP

# include <stdexcept>
# include <iostream>

class Brakes
{
	public:
		const static float EMERGENCY_FORCE;

		Brakes() {}

		Brakes(const Brakes &) {}

		Brakes &operator=(const Brakes &) { return (*this); }

		~Brakes() {}

		void apply_force(const float force)
		{
			if (force > EMERGENCY_FORCE)
				throw std::invalid_argument("Force requested to apply exceeds maximum brake force");
			std::cout << "Applied force " << force << " on brakes" << std::endl;
		}

		void apply_emergency()
		{
			apply_force(EMERGENCY_FORCE);
		}
};

const float Brakes::EMERGENCY_FORCE = 1000.f;

#endif
