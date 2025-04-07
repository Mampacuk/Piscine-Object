#include "headmaster.hpp"

std::ostream &operator<<(std::ostream &o, const Headmaster &h)
{
	o << "Headmaster(formToValidate: ";
	return (h.print_forms(o) << ", " << static_cast<const Staff&>(h) << ")");
}
