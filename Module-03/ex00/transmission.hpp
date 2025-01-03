#ifndef TRANSMISSION_HPP
# define TRANSMISSION_HPP

# include <stdexcept>
# include <iostream>

class Transmission
{
	public:
		enum Gear
		{
			ONE,
			TWO,
			THREE,
			FOUR,
			FIVE,
			SIX,
			REVERSE
		};

		Transmission() : _gear(ONE) {}

		Transmission(const Transmission &other)
		{
			*this = other;
		}

		Transmission &operator=(const Transmission &other)
		{
			_gear = other._gear;
			return (*this);
		}

		~Transmission() {}

		void shift_gears_up()
		{
			if (_gear == REVERSE)
				throw std::runtime_error("Can't shift gear up from reverse gear");
			_gear = static_cast<Gear>(static_cast<int>(_gear) + 1);
			std::cout << "Shifted gear up" << std::endl;
		}

		void shift_gears_down()
		{
			if (_gear == ONE)
				throw std::runtime_error("Can't shift gear down from gear one");
			_gear = static_cast<Gear>(static_cast<int>(_gear) - 1);
			std::cout << "Shifted gear down" << std::endl;
		}

		void reverse()
		{
			_gear = REVERSE;
			std::cout << "Shifted gear to reverse" << std::endl;
		}

	private:
		Gear _gear;
};

#endif
