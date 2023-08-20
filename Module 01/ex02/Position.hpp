#ifndef POSITION_HPP
# define POSITION_HPP

# include <iostream>

struct Position
{
	int x;
	int y;
	int z;
	Position();
	~Position();
	Position(int x, int y, int z);
	Position(const Position &copy);
	Position &operator=(const Position &rhs);
};

std::ostream &operator<<(std::ostream &o, const Position &p);

#endif
