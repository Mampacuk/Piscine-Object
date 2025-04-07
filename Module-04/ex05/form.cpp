#include "form.hpp"
#include "form_type.hpp"

bool Form::get_signed(const Staff&)
{
	if (!(_signed = is_complete()))
		std::cout << *this << " was not signed: its mandatory info is not complete" << std::endl;
	return (_signed);
}

bool Form::execute()
{
	if (_signed)
		execute_impl();
	else
		std::cout << *this << " was not executed because it was not signed" << std::endl;
	return (_signed);
}

std::ostream &operator<<(std::ostream &o, const Form &f)
{
	return (o << form_type_names[static_cast<int>(f.form_type())]);
}
