#include "professor.hpp"
#include "course.hpp"
#include "forms.hpp"
#include "headmaster.hpp"
#include "school.hpp"
#include "rooms.hpp"
#include "student.hpp"

namespace
{
	const auto is_free_classroom = [](const std::shared_ptr<Room> &room)
									{ if (auto classroom = std::dynamic_pointer_cast<Classroom>(room);
									  	classroom && classroom->get_occupants().empty())
										return (true);
								  	  return (false); };
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
	if (auto classroom_it = std::find_if(school->get_rooms().begin(), school->get_rooms().end(), is_free_classroom);
		classroom_it != school->get_rooms().end())
		classroom = std::static_pointer_cast<Classroom>(*classroom_it);
	else
	{
		auto classroom_creation_form = std::static_pointer_cast<NeedMoreClassRoomForm>(ft::weak_lock(headmaster->request_form(FormType::NeedMoreClassRoom)));
		classroom_creation_form->set_school(school);
		classroom_creation_form->set_course(_currentCourse);
		headmaster->sign_and_execute(std::move(classroom_creation_form));
		classroom = std::static_pointer_cast<Classroom>(*std::find_if(school->get_rooms().begin(), school->get_rooms().end(), is_free_classroom));
	}
	classroom->enter(weak_from_this());
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
	classroom->exit(weak_from_this());
	headmaster->sign_and_execute_all_forms();
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
