#include "headmaster.hpp"
#include "secretary.hpp"
#include "form.hpp"
#include "school.hpp"
#include "professor.hpp"
#include "student.hpp"
#include "rooms.hpp"
#include "bell.hpp"

Headmaster::Headmaster(const std::string &p_name, std::weak_ptr<School> school) : Staff(p_name), _school(std::move(school)), _bell(std::make_shared<Bell>()) {}

std::ostream &operator<<(std::ostream &o, const Headmaster &h)
{
	o << "Headmaster(formToValidate: ";
	return (h.print_forms(o) << ", " << static_cast<const Staff&>(h) << ")");
}

std::weak_ptr<Form> Headmaster::receiveForm(std::shared_ptr<Form> p_form)
{
	if (p_form)
	{
		if (!in_room<HeadmasterOffice>())
			throw std::runtime_error("Headmaster " + name() + " is not in their office to work");
		std::cout << "Headmaster " << name() << " received a " << *p_form << " form" << std::endl;
		_formToValidate.push_back(p_form);
	}
	return (p_form);
}

std::weak_ptr<Form> Headmaster::request_form(FormType form_type)
{
	if (!in_room<HeadmasterOffice>())
		throw std::runtime_error("Headmaster " + name() + " is not in their office to work");
	return (receiveForm(ft::weak_lock(ft::weak_lock(_school)->getSecretary())->createForm(form_type)));
}

void Headmaster::sign_and_execute(std::weak_ptr<Form> form_to_validate)
{
	if (!in_room<HeadmasterOffice>())
		throw std::runtime_error("Headmaster " + name() + " is not in their office to work");
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
	if (!in_room<HeadmasterOffice>())
		throw std::runtime_error("Headmaster " + name() + " is not in their office to work");
	while (!_formToValidate.empty())
	{
		sign(_formToValidate.back());
		_formToValidate.back()->execute();
		_formToValidate.pop_back();
	}
}

void Headmaster::make_professors_do_class() const
{
	if (!in_room<HeadmasterOffice>())
		throw std::runtime_error("Headmaster " + name() + " is not in their office to work");
	for (auto &professor : ft::weak_lock(_school)->getProfessors())
		professor->acquire_course();
	for (auto &student : ft::weak_lock(_school)->getStudents())
		student->search_class();
	for (auto &professor : ft::weak_lock(_school)->getProfessors())
		professor->doClass();
}

void Headmaster::on_event(Event event)
{
	auto current_room = room().lock();
	switch (event)
	{
	case Event::RingBell:
		if (std::dynamic_pointer_cast<HeadmasterOffice>(current_room))
		{
			current_room->exit(weak_from_this());
			ft::weak_lock(ft::weak_lock(_school)->find_room<StaffRestRoom>())->enter(weak_from_this());
		}
		else if (std::dynamic_pointer_cast<StaffRestRoom>(current_room))
		{
			current_room->exit(weak_from_this());
			ft::weak_lock(ft::weak_lock(_school)->find_room<HeadmasterOffice>())->enter(weak_from_this());
		}
		else
			throw std::runtime_error("Headmaster " + name() + " is not in a correct room to react to the bell");
	}
}

void Headmaster::ring_bell()
{
	_bell->ring();
}
