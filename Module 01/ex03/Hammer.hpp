#ifndef HAMMER_HPP
# define HAMMER_HPP

# include "Tool.hpp"

# include <iostream>

class Hammer : public Tool
{
	public:
		Hammer();
		~Hammer();
		void use();
	private:
		// delete {
		Hammer(const Hammer &copy);
		Hammer &operator=(const Hammer &copy);
		// } delete
};

std::ostream &operator<<(std::ostream &o, const Hammer &h);

#endif
