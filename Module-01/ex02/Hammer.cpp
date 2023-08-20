#include "Hammer.hpp"

Hammer::Hammer() : Tool()
{
	std::cout << *this << " default-constructed" << std::endl;
}

Hammer::~Hammer()
{
	std::cout << *this << " destroyed" << std::endl;
}

void Hammer::use()
{
	increment_usage();
	std::cout << "* slam-slam!!! * " << *this << " got used by " << *get_owner() << std::endl;
}

std::ostream &operator<<(std::ostream &o, const Hammer &s)
{
	o << "Hammer<=" << static_cast<const Tool&>(s);
	return (o);
}
