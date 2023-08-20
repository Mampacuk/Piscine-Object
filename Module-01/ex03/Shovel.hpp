#ifndef SHOVEL_HPP
# define SHOVEL_HPP

# include "Tool.hpp"

# include <iostream>

class Shovel : public Tool
{
	public:
		Shovel();
		~Shovel();
		void use();
	private:
		// delete {
		Shovel(const Shovel &copy);
		Shovel &operator=(const Shovel &copy);
		// } delete
};

std::ostream &operator<<(std::ostream &o, const Shovel &s);

#endif
