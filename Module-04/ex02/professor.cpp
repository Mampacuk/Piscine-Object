#include "professor.hpp"
#include "course.hpp"

std::ostream &operator<<(std::ostream &o, const Professor &s)
{
	o << "Professor(currentCourse: ";
	if (const auto course = s.current_course())
	{
		o << "Course(name: " << course->name() << ", responsible: this, students: ";
		course->print_students(o) << ", numberOfClassToGraduate: " << course->classes_to_graduate() << ", maximumNumberOfStudent: " << course->capacity() << ")";
	}
	else
		o << "(null)";
	return (o << ", " << static_cast<const Staff&>(s) << ")");
}
