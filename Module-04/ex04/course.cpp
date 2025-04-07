#include "course.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "rooms.hpp"

size_t Course::_global_id = 0;

void Course::mark_attendance(std::weak_ptr<Student> student)
{
	const auto prof = ft::weak_lock(_responsible);
	const auto prof_room = std::dynamic_pointer_cast<Classroom>(ft::weak_lock(prof->room()));
	if (!prof_room)
		throw std::runtime_error("Professor " + prof->name() + " is not in a classroom to mark attendance");
	auto stud = ft::weak_lock(student);
	auto stud_room = std::dynamic_pointer_cast<Classroom>(ft::weak_lock(prof->room()));
	if (!stud_room)
		throw std::runtime_error("Student " + stud->name() + " is not in a classroom to get their attendance marked");
	if (stud_room != prof_room)
		throw std::runtime_error("Student " + stud->name() + " and professor " + prof->name() + " are not in the same room");
	auto prof_course = ft::weak_lock(prof_room->current_course());
	if (prof_course.get() != this)
		throw std::runtime_error("Professor " + prof->name() + " is not in a classroom for " + name() + "; it's for " + prof_course->name() + " instead");
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
