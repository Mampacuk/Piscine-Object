#include "student.hpp"
#include "course.hpp"

std::ostream &Student::print_subscribed_courses(std::ostream &o) const
{
	return (ft::print_shared_ptr_container_field(o, _subscribedCourses, &Course::name));
}

std::ostream &operator<<(std::ostream &o, const Student &s)
{
	o << "Student(subscribedCourses: ";
	return (s.print_subscribed_courses(o) << ", " << static_cast<const Person&>(s) << ")");
}
