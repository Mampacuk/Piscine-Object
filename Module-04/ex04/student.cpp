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
		throw std::runtime_error("Student " + name() + " couldn't enter classroom with course " + course->name());
	course->mark_attendance(weak_from_this());
}

void Student::graduate(std::weak_ptr<Course> p_course)
{
	if (ft::weak_ptr_erase(_subscribedCourses, p_course))
		std::cout << name() << " graduated from " << ft::weak_lock(p_course)->name() << std::endl;
}

void Student::exitClass()
{
	if (auto current_room = room().lock(); current_room && std::dynamic_pointer_cast<Classroom>(current_room))
		current_room->exit(weak_from_this());
}

void Student::on_event(Event event)
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
			if (!_subscribedCourses.empty())
			{
				current_room->exit(weak_from_this());
				ft::weak_lock(ft::weak_lock(_school)->find_room<Classroom>([this](const Classroom &classroom)
					{ if (auto course = classroom.current_course().lock(); course && course->subscribed_to_by(weak_from_this()))
						return (true);
					  return (false); }))->enter(weak_from_this());
			}
		}
		else
			throw std::runtime_error("Student " + name() + " is not in a correct room to react to the bell");
	}
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
