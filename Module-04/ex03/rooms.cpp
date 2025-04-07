#include "rooms.hpp"
#include "professor.hpp"
#include "student.hpp"
#include "course.hpp"
#include "headmaster.hpp"
#include "secretary.hpp"

bool Room::enter(std::weak_ptr<Person> person)
{
	if (canEnter(person))
	{
		auto person_to_enter = ft::weak_lock(person);
		std::cout << person_to_enter->name() << " has entered room(" << ID << ")" << std::endl;
		_occupants.push_back(std::move(person));
		person_to_enter->set_room(weak_from_this());
		return (true);
	}
	return (false);
}

void Room::exit(std::weak_ptr<Person> person)
{
	auto person_to_exit = ft::weak_lock(person);
	if (shared_from_this() == ft::weak_lock(person_to_exit->room()) && ft::weak_ptr_erase(_occupants, person))
	{
		person_to_exit->set_room(std::weak_ptr<Room>());
		std::cout << person_to_exit->name() << " has left room(" << ID << ")" << std::endl;
	}
}

std::ostream &operator<<(std::ostream &o, const Room &r)
{
	o << "Room(ID: " << r.id() <<  ", occupants: ";
	return (r.print_occupants(o) << ")");
}

bool Classroom::canEnter(std::weak_ptr<Person> person) const
{
	auto person_to_enter = ft::weak_lock(person);
	auto room_course = _currentCourse.lock();
	if (!room_course)
	{
		std::cout << person_to_enter->name() << " can't enter because classroom(" << std::to_string(id()) << ") has no course" << std::endl;
		return (false);
	}
	if (auto professor = std::dynamic_pointer_cast<Professor>(person_to_enter))
	{
		if (professor->current_course().lock() == room_course)
			return (true);
		else
		{
			std::cout << "Professor " << professor->name() << " can't enter classroom(" << std::to_string(id()) << ") because they don't curate course " << room_course->name() << std::endl;
			return (false);
		}
	}
	else if (auto student = std::dynamic_pointer_cast<Student>(person_to_enter))
	{
		if (room_course->subscribed_to_by(student))
			return (true);
		else
		{
			std::cout << "Student " << student->name() << " can't enter classroom(" << std::to_string(id()) << ") because they are not subscribed to course " << room_course->name() << std::endl;
			return (false);
		}
	}
	return (false);
}

std::ostream &operator<<(std::ostream &o, const Classroom &c)
{
	o << "Classroom(currentCourse: ";
	return (ft::print_shared_ptr(o, ft::weak_lock(c.current_course())) << ", " << static_cast<const Room&>(c) << ")");
}

bool SecretarialOffice::canEnter(std::weak_ptr<Person> person) const
{
	return (static_cast<bool>(std::dynamic_pointer_cast<Secretary>(person.lock())));
}

std::ostream &operator<<(std::ostream &o, const SecretarialOffice &s)
{
	o << "SecretarialOffice(archivedForms: ";
	return (s.printArchivedForms(o) << ", " << static_cast<const Room&>(s) << ")");
}

bool HeadmasterOffice::canEnter(std::weak_ptr<Person> person) const
{
	return (static_cast<bool>(std::dynamic_pointer_cast<Headmaster>(person.lock())));
}

std::ostream &operator<<(std::ostream &o, const HeadmasterOffice &h)
{
	return (o << "HeadmasterOffice(" << static_cast<const Room&>(h) << ")");
}

bool StaffRestRoom::canEnter(std::weak_ptr<Person> person) const
{
	return (static_cast<bool>(std::dynamic_pointer_cast<Staff>(person.lock())));
}

std::ostream &operator<<(std::ostream &o, const StaffRestRoom &s)
{
	return (o << "StaffRestRoom(" << static_cast<const Room&>(s) << ")");
}

std::ostream &operator<<(std::ostream &o, const Courtyard &c)
{
	return (o << "Courtyard(" << static_cast<const Room&>(c) << ")");
}
