#include "Statistic.hpp"

Statistic::Statistic() : level(), exp()
{
	std::cout << *this << " default-constructed" << std::endl;
}

Statistic::~Statistic()
{
	std::cout << *this << " destroyed" << std::endl;
}

Statistic::Statistic(int level, int exp) : level(level), exp(exp)
{
	std::cout << *this << " arg-constructed" << std::endl;
}

Statistic::Statistic(const Statistic &copy) : level(copy.level), exp(copy.exp)
{
	std::cout << "Statistic copy-constructed from " << copy << std::endl;
}

Statistic &Statistic::operator=(const Statistic &rhs)
{
	std::cout << *this << " assigned to " << rhs << std::endl;
	level = rhs.level;
	exp = rhs.exp;
	return (*this);
}

std::ostream &operator<<(std::ostream &o, const Statistic &p)
{
	o << "Statistic(level: " << p.level << ", exp: " << p.exp << ")";
	return (o);
}
