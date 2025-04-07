#include "course.hpp"
#include "student.hpp"
#include "professor.hpp"

std::ostream &Course::print_students(std::ostream &o) const
{
	return (ft::print_container(o, _students, [](std::ostream &o, const std::weak_ptr<Student> &student) { ft::print_shared_ptr(o, student.lock()); }));
}

std::ostream &operator<<(std::ostream &o, const Course &c)
{
	o << "Course(name: " << c.name() <<  ", responsible: ";
	if (const auto professor = c.responsible().lock())
		std::cout << "Professor(currentCourse: this, " << static_cast<const Staff&>(*professor) << ")";
	else
		std::cout << "(null)";
	std::cout << ", students: ";
	return (c.print_students(o) << ", numberOfClassToGraduate: " << c.classes_to_graduate() << ", maximumNumberOfStudent: " << c.capacity() << ")");
}
