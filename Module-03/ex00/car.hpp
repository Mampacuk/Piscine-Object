#ifndef CAR_HPP
# define CAR_HPP

# include "brakes.hpp"
# include "engine.hpp"
# include "transmission.hpp"
# include "wheels.hpp"

// Car has a single responsibility of only managing its own parts.
// it delegates responsibility for actions such as braking to brakes,
// turning wheels to wheels themselves, etc. so if for any of those processes
// changes are requested, one would modify not the car class, but the designated
// car part classes. this decreases chances of creating bugs when changing
// the car class.
// src: https://blog.cleancoder.com/uncle-bob/2014/05/08/SingleReponsibilityPrinciple.html
class Car
{
	public:
		Car() {}

		Car(const Car &other)
		{
			*this = other;
		}

		Car &operator=(const Car &other)
		{
			_wheels = other._wheels;
			_brakes = other._brakes;
			_engine = other._engine;
			_transmission = other._transmission;
			return (*this);
		}

		~Car() {}

		void start()
		{
			_engine.start();
		}

		void stop()
		{
			_engine.stop();
		}

		void accelerate(const float speed)
		{
			_engine.accelerate(speed);
		}

		void shift_gears_up()
		{
			_transmission.shift_gears_up();
		}

		void shift_gears_down()
		{
			_transmission.shift_gears_down();
		}

		void reverse()
		{
			_transmission.reverse();
		}

		void turn_wheel(const float angle)
		{
			_wheels.turn(angle);
		}

		void straighten_wheels()
		{
			_wheels.straighten();
		}

		void apply_force_on_brakes(const float force)
		{
			_brakes.apply_force(force);
		}

		void apply_emergency_brakes()
		{
			_brakes.apply_emergency();
		}

	private:
		Wheels _wheels;
		Brakes _brakes;
		Engine _engine;
		Transmission _transmission;
};

#endif
