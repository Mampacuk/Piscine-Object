#include "professor.hpp"
#include "course.hpp"
#include "forms.hpp"
#include "headmaster.hpp"
#include "school.hpp"
#include "rooms.hpp"
#include "student.hpp"

namespace
{
	const auto is_free_classroom = [](const Classroom &classroom) { return (classroom.get_occupants().empty()); };
}

void Professor::assignCourse(std::shared_ptr<Course> p_course)
{
	_currentCourse = std::move(p_course);
	std::cout << "Professor " << name() << " was assigned course " << _currentCourse->name() << std::endl;
}

void Professor::acquire_course()
{
	if (!_currentCourse)
	{
		auto headmaster = ft::weak_lock(ft::weak_lock(_school)->getHeadmaster());
		auto course_creation_form = std::static_pointer_cast<NeedCourseCreationForm>(ft::weak_lock(headmaster->request_form(FormType::NeedCourseCreation)));
		course_creation_form->set_professor(weak_from_this());
		headmaster->sign_and_execute(course_creation_form);
	}
}

void Professor::doClass()
{
	if (!_currentCourse)
		acquire_course();
	auto school = ft::weak_lock(_school);
	auto headmaster = ft::weak_lock(school->getHeadmaster());
	std::shared_ptr<Classroom> classroom;
	if (auto current_room = std::dynamic_pointer_cast<Classroom>(room().lock()); current_room && current_room->inside(weak_from_this())
		&& ft::weak_lock(current_room->current_course()) == _currentCourse)
		classroom = current_room;
	else
	{
		if (auto room = school->find_room<Classroom>(is_free_classroom).lock())
			classroom = room;
		else
		{
			auto classroom_creation_form = std::static_pointer_cast<NeedMoreClassRoomForm>(ft::weak_lock(headmaster->request_form(FormType::NeedMoreClassRoom)));
			classroom_creation_form->set_school(school);
			classroom_creation_form->set_course(_currentCourse);
			headmaster->sign_and_execute(std::move(classroom_creation_form));
			classroom = ft::weak_lock(school->find_room<Classroom>(is_free_classroom));
		}
		classroom->enter(weak_from_this());
	}
	for (const auto &[student, classes_attended] : _currentCourse->get_attendance())
	{
		if (classes_attended >= _currentCourse->classes_to_graduate())
		{
			auto graduation_form = std::static_pointer_cast<CourseFinishedForm>(ft::weak_lock(headmaster->request_form(FormType::CourseFinished)));
			graduation_form->set_alumnus(student);
			graduation_form->set_course(_currentCourse);
		}
		else
			ft::weak_lock(student)->attendClass(classroom);
	}
	headmaster->sign_and_execute_all_forms();
}

void Professor::on_event(Event event)
{
	auto current_room = room().lock();
	switch (event)
	{
	case Event::RingBell:
		if (auto classroom = std::dynamic_pointer_cast<Classroom>(current_room))
		{
			current_room->exit(weak_from_this());
			ft::weak_lock(ft::weak_lock(_school)->find_room<Courtyard>())->enter(weak_from_this());
		}
		else if (std::dynamic_pointer_cast<Courtyard>(current_room))
		{
			if (_currentCourse)
			{
				current_room->exit(weak_from_this());
				ft::weak_lock(ft::weak_lock(_school)->find_room<Classroom>([this](const Classroom &classroom)
					{ return (classroom.current_course().lock() == _currentCourse); }))->enter(weak_from_this());
			}
		}
		else
			throw std::runtime_error("Professor " + name() + " is not in a correct room to react to the bell");
	}
}

std::ostream &operator<<(std::ostream &o, const Professor &s)
{
	o << "Professor(currentCourse: ";
	if (const auto course = s.current_course().lock())
	{
		o << "Course(name: " << course->name() << ", responsible: this, students: ";
		course->print_students(o) << ", numberOfClassToGraduate: " << course->classes_to_graduate() << ", maximumNumberOfStudent: " << course->capacity() << ")";
	}
	else
		o << "(null)";
	return (o << ", " << static_cast<const Staff&>(s) << ")");
}
