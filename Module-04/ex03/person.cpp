#include "person.hpp"

size_t Person::_global_id = 0;

std::ostream &operator<<(std::ostream &o, const Person &p)
{
	o << "Person(name: " << p.name() <<  ", currentRoom: ";
	return (ft::print_shared_ptr(o, p.room().lock()) << ")");
}
