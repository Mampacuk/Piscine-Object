#include "staff.hpp"
#include "form.hpp"
#include "headmaster.hpp"

bool Staff::sign(std::weak_ptr<Form> p_form)
{
	auto form = ft::weak_lock(p_form);
	if (dynamic_cast<Headmaster*>(this) && form->get_signed(*this))
	{
		std::cout << "Staff " << name() << " has managed to sign " << *form << std::endl;
		return (true);
	}
	else
		std::cout << *this << " could not sign " << *form << std::endl;
	return (false);
}

std::ostream &operator<<(std::ostream &o, const Staff &s)
{
	return (o << "Staff(" << static_cast<const Person&>(s) << ")");
}
