#include "car.hpp"

int main()
{
	Car car;

	car.start();

	car.accelerate(120.5f);

	car.shift_gears_up();
	car.shift_gears_down();
	car.reverse();

	car.turn_wheel(-15.f);
	car.straighten_wheels();
	car.turn_wheel(1.f);

	car.apply_force_on_brakes(17.f);
	car.apply_emergency_brakes();

	car.stop();
}
