#include "staff.hpp"
#include "form.hpp"
#include "headmaster.hpp"

bool Staff::sign(std::shared_ptr<Form> p_form)
{
	if (p_form)
	{
		if (dynamic_cast<Headmaster*>(this) && p_form->get_signed(*this))
		{
			std::cout << *this << " has managed to sign " << *p_form << std::endl;
			return (true);
		}
		else
			std::cout << *this << " could not sign " << *p_form << std::endl;
	}
	return (false);
}

std::ostream &operator<<(std::ostream &o, const Staff &s)
{
	return (o << "Staff(" << static_cast<const Person&>(s) << ")");
}
