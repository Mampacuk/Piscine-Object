#include "course.hpp"
#include "student.hpp"
#include "professor.hpp"

size_t Course::_global_id = 0;

void Course::mark_attendance(std::weak_ptr<Professor> professor, std::weak_ptr<Student> student)
{
	auto prof = ft::weak_lock(professor);
	auto stud = ft::weak_lock(student);
	if (prof != ft::weak_lock(_responsible))
		throw std::invalid_argument("Professor " + prof->name() + " not responsible for course tried to increment attendance of student " + stud->name() + " in course " + name());
	unsigned int &attendance = _attendance.at(student);
	std::cout << "Professor " << prof->name() << " has marked attendance of " << stud->name() << " in course " << name() << " (from " << attendance << " to " << attendance + 1 << ")" << std::endl;
	attendance++;
}

void Course::assign(std::weak_ptr<Professor> p_professor)
{
	_responsible = std::move(p_professor);
	std::cout << "Course " << name() << " is now curated by professor " << ft::weak_lock(_responsible)->name() << std::endl;
}

void Course::subscribe(std::weak_ptr<Student> p_student)
{
	if (_attendance.find(p_student) == _attendance.end())
	{
		std::cout << "Student " << ft::weak_lock(p_student)->name() << " subscribed to course " << name() << std::endl;
		_attendance.emplace(std::move(p_student), 0);
	}
}

void Course::unsubscribe(std::weak_ptr<Student> p_student)
{
	if (_attendance.erase(p_student))
		std::cout << ft::weak_lock(p_student)->name() << " was unsubscribed from " << name() << std::endl;
}

std::ostream &Course::print_students(std::ostream &o) const
{
	return (ft::print_container(o, _attendance, [](std::ostream &o, const attendance::value_type &pair) { o << ft::weak_lock(pair.first) << " : " << pair.second; }));
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
