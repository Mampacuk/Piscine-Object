#ifndef OBSERVER_HPP
# define OBSERVER_HPP

# include "event.hpp"

class Observer
{
public:
	virtual void on_event(Event event) = 0;
	virtual ~Observer() = default;
};

#endif
