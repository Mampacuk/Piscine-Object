#include "Shovel.hpp"

Shovel::Shovel() : numberOfUses(0), owner()
{
	std::cout << *this << " default-constructed" << std::endl;
}

Shovel::~Shovel()
{
	if (owner)
		owner->unset_tool();
	std::cout << *this << " destroyed" << std::endl;
}

std::ostream &operator<<(std::ostream &o, const Shovel &p)
{
	o << "Shovel(numberOfUses: " << p.numberOfUses;
	if (p.owner)
		o << ", owner: " << *p.owner;
	o << ")";
	return (o);
}
