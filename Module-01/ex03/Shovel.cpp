#include "Shovel.hpp"

Shovel::Shovel() : Tool()
{
	std::cout << *this << " default-constructed" << std::endl;
}

Shovel::~Shovel()
{
	std::cout << *this << " destroyed" << std::endl;
}

void Shovel::use()
{
	increment_usage();
	std::cout << "* dig-dig!!! * " << *this << " got used by " << *get_owner() << std::endl;
}

std::ostream &operator<<(std::ostream &o, const Shovel &s)
{
	o << "Shovel<=" << static_cast<const Tool&>(s);
	return (o);
}
