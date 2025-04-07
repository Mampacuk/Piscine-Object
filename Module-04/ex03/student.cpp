#include "student.hpp"
#include "course.hpp"
#include "rooms.hpp"
#include "professor.hpp"
#include "school.hpp"
#include "forms.hpp"
#include "headmaster.hpp"

void Student::enroll(std::weak_ptr<Course> course)
{
	if (!ft::weak_ptr_contains(_subscribedCourses, course))
	{
		std::cout << "Student " << name() << " enrolled in course " << ft::weak_lock(course)->name() << std::endl;
		_subscribedCourses.push_back(std::move(course));
	}
}

void Student::search_class()
{
	auto school = ft::weak_lock(_school);
	if (auto professor = std::find_if(school->getProfessors().begin(), school->getProfessors().end(),
									  [](const std::shared_ptr<Professor> &prof)
									  { if (!prof) return (false);
										if (auto course = ft::weak_lock(prof->current_course()); course && course->capacity() != course->get_attendance().size())
											return (true);
										return (false); });
		professor != school->getProfessors().end())
	{
		auto headmaster = ft::weak_lock(ft::weak_lock(_school)->getHeadmaster());
		auto subscription_to_course = std::static_pointer_cast<SubscriptionToCourseForm>(ft::weak_lock(headmaster->request_form(FormType::SubscriptionToCourse)));
		subscription_to_course->set_course((*professor)->current_course());
		subscription_to_course->set_student(weak_from_this());
		headmaster->sign_and_execute(std::move(subscription_to_course));
	}
}

void Student::attendClass(std::weak_ptr<Classroom> p_classroom)
{
	auto classroom = ft::weak_lock(p_classroom);
	auto course = classroom->current_course().lock();
	if (!course)
		throw std::runtime_error("Student " + name() + " attempted to attend classroom with no course");
	if (!classroom->enter(weak_from_this()))
		throw std::runtime_error("Student " + name() + " couldn't enter the classroom with course " + course->name());
	course->mark_attendance(course->responsible(), weak_from_this());
	exitClass(classroom);
}

void Student::graduate(std::weak_ptr<Course> p_course)
{
	if (ft::weak_ptr_erase(_subscribedCourses, p_course))
			std::cout << name() << " graduated from " << ft::weak_lock(p_course)->name() << std::endl;
}

void Student::exitClass(std::weak_ptr<Classroom> classroom)
{
	ft::weak_lock(classroom)->exit(weak_from_this());
}

std::ostream &Student::print_subscribed_courses(std::ostream &o) const
{
	return (ft::print_weak_ptr_container_field(o, _subscribedCourses, Course::name));
}

std::ostream &operator<<(std::ostream &o, const Student &s)
{
	o << "Student(subscribedCourses: ";
	return (s.print_subscribed_courses(o) << ", " << static_cast<const Person&>(s) << ")");
}
