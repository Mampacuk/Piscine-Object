#ifndef SHOVEL_HPP
# define SHOVEL_HPP

# include <iostream>

class Worker;

struct Shovel
{
	int numberOfUses;
	Worker *owner;
	Shovel();
	~Shovel();

	private:
		// deleted {
		Shovel(const Shovel &copy);
		Shovel &operator=(const Shovel &copy);
		// } deleted
};

std::ostream &operator<<(std::ostream &o, const Shovel &s);

# include "Worker.hpp"

#endif
