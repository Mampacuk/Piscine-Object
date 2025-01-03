#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <stdexcept>
# include <iostream>

class Engine
{
	public:
		Engine() : _started(false), _speed(0.f) {}

		~Engine() {}

		Engine(const Engine &other)
		{
			*this = other;
		}

		Engine &operator=(const Engine &other)
		{
			_started = other._started;
			_speed = other._speed;
			return (*this);
		}

		void start()
		{
			if (_started)
				throw std::runtime_error("Engine is already started");
			_started = true;
			std::cout << "Engine started" << std::endl;
		}

		void stop()
		{
			if (!_started)
				throw std::runtime_error("Engine is already stopped");
			_started = false;
			std::cout << "Engine stopped" << std::endl;
		}

		void accelerate(const float speed)
		{
			if (!_started)
				throw std::runtime_error("Can't accelerate when the engine is not started");
			const float old_speed = _speed;
			_speed += speed;
			std::cout << "Engine accelerated from " << old_speed << " to " << _speed << std::endl;
		}

	private:
		bool _started;
		float _speed;
};

#endif
