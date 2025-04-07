#ifndef COURSES_HPP
# define COURSES_HPP

# include "common.hpp"
# include <iostream>
# include <string>
# include <list>

class Student;
class Professor;

class Course
{
private:
	std::string _name;
	std::weak_ptr<Professor> _responsible;
	std::list<std::shared_ptr<Student>> _students;
	int _numberOfClassToGraduate;
	int _maximumNumberOfStudent;
public:
	Course() = default;
	Course(Course&&) = default;
	Course(const Course&) = default;
	Course(const std::string &name, int num_class_to_graduate = 0, int max_num_students = 0) : _name(name), _responsible(), _students(), _numberOfClassToGraduate(num_class_to_graduate), _maximumNumberOfStudent(max_num_students) {}
	Course &operator=(const Course&) = default;
	~Course() = default;
	Course(const std::string &p_name) : _name(p_name), _responsible(), _students() {}
	void assign(std::shared_ptr<Professor> p_professor) { _responsible = std::move(p_professor); }
	void subscribe(std::shared_ptr<Student> p_student) { _students.push_back(std::move(p_student)); }
	const std::string &name() const { return (_name); }
	std::weak_ptr<Professor> responsible() const { return (_responsible); }
	std::ostream &printStudents(std::ostream &o = std::cout) const { return (ft::print_shared_ptr_container(o, _students)); }
	int number_of_class_to_graduate() const { return (_numberOfClassToGraduate); }
	int maximum_number_of_students() const { return (_maximumNumberOfStudent); }
};

std::ostream &operator<<(std::ostream &o, const Course &c)
{
	o << "Course(name: " << c.name() <<  ", responsible: ";
	auto professor = c.responsible().lock();
	o << (!professor ? "(null)" : professor->name()) << ", students: ";
	return (c.printStudents(o) << ", numberOfClassToGraduate: " << c.number_of_class_to_graduate() << ", maximumNumberOfStudent: " << c.maximum_number_of_students() << ")");
}

#endif
