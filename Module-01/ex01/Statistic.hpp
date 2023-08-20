#ifndef STATISTIC_HPP
# define STATISTIC_HPP

# include <iostream>

struct Statistic
{
	int level;
	int exp;
	Statistic();
	~Statistic();
	Statistic(int level, int exp);
	Statistic(const Statistic &copy);
	Statistic &operator=(const Statistic &rhs);
};

std::ostream &operator<<(std::ostream &o, const Statistic &s);

#endif
