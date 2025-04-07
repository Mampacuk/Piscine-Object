#ifndef COURSES_HPP
# define COURSES_HPP

# include <string>
# include <list>

class Student;
class Professor;

class Course
{
private:
	std::string _name;
	std::shared_ptr<Professor> _responsible;
	std::list<std::shared_ptr<Student>> _students;
	int _numberOfClassToGraduate;
	int _maximumNumberOfStudent;
public:
	Course(std::string p_name);
	void assign(std::shared_ptr<Professor> p_professor);
	void subscribe(std::shared_ptr<Student> p_student);
};

#endif
