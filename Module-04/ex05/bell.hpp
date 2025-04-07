#ifndef BELL_HPP
# define BELL_HPP

# include "common.hpp"
# include "observer.hpp"

class Bell
{
public:
	Bell() = default;
	Bell(Bell&&) = default;
	Bell(const Bell&) = default;
	Bell &operator=(const Bell&) = default;
	~Bell() = default;

	void subscribe(std::weak_ptr<Observer> observer)
	{
		_observers.emplace(std::move(observer));
	}
	void unsubscribe(std::weak_ptr<Observer> observer)
	{
		_observers.erase(observer);
	}
	void ring()
	{
		std::cout << " > > > > THE BELL HAS RUNG! < < < < " << std::endl;
		for (auto it = _observers.begin(); it != _observers.end();)
		{
			if (auto observer = it->lock())
			{
				observer->on_event(Event::RingBell);
				it++;
			}
			else
				it = _observers.erase(it);
		}
	}
private:
	std::set<std::weak_ptr<Observer>, ft::weak_less<Observer>> _observers;
};

#endif
