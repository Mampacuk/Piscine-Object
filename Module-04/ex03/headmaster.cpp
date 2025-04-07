#include "headmaster.hpp"
#include "secretary.hpp"
#include "form.hpp"
#include "school.hpp"
#include "professor.hpp"
#include "student.hpp"

std::ostream &operator<<(std::ostream &o, const Headmaster &h)
{
	o << "Headmaster(formToValidate: ";
	return (h.print_forms(o) << ", " << static_cast<const Staff&>(h) << ")");
}

std::weak_ptr<Form> Headmaster::receiveForm(std::shared_ptr<Form> p_form)
{
	if (p_form)
	{
		std::cout << "Headmaster " << name() << " received a " << *p_form << " form" << std::endl;
		_formToValidate.push_back(p_form);
	}
	return (p_form);
}

std::weak_ptr<Form> Headmaster::request_form(FormType form_type)
{
	return (receiveForm(ft::weak_lock(ft::weak_lock(_school)->getSecretary())->createForm(form_type)));
}

void Headmaster::sign_and_execute(std::weak_ptr<Form> form_to_validate)
{
	auto form = ft::weak_lock(form_to_validate);
	if (std::find(_formToValidate.begin(), _formToValidate.end(), form) != _formToValidate.end())
	{
		sign(form);
		form->execute();
		ft::erase(_formToValidate, form);
	}
}

void Headmaster::sign_and_execute_all_forms()
{
	while (!_formToValidate.empty())
	{
		sign(_formToValidate.back());
		_formToValidate.back()->execute();
		_formToValidate.pop_back();
	}
}

void Headmaster::make_professors_do_class() const
{
	for (auto &professor : ft::weak_lock(_school)->getProfessors())
		professor->acquire_course();
	for (auto &student : ft::weak_lock(_school)->getStudents())
		student->search_class();
	for (auto &professor : ft::weak_lock(_school)->getProfessors())
		professor->doClass();
}