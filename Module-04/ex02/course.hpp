#ifndef COURSES_HPP
# define COURSES_HPP

# include "common.hpp"

class Course
{
private:
	std::string _name;
	std::weak_ptr<Professor> _responsible;
	std::vector<std::weak_ptr<Student>> _students;
	int _numberOfClassToGraduate;
	int _maximumNumberOfStudent;
public:
	Course() = default;
	Course(Course&&) = default;
	Course(const Course&) = default;
	Course(const std::string &name, int num_class_to_graduate = 0, int max_num_students = 0) : _name(name), _responsible(), _students(), _numberOfClassToGraduate(num_class_to_graduate), _maximumNumberOfStudent(max_num_students) {}
	Course &operator=(const Course&) = default;
	~Course() {}
	Course(const std::string &p_name) : _name(p_name), _responsible(), _students() {}
	// setters
	void assign(std::shared_ptr<Professor> p_professor)
	{
		_responsible = std::move(p_professor);
		std::cout << *this << " is now curated by " << *ft::weak_lock(_responsible) << std::endl;
	}
	void subscribe(std::weak_ptr<Student> p_student)
	{
		if (std::find_if(_students.begin(), _students.end(), [&p_student](const std::weak_ptr<Student> &student) { return (ft::weak_lock(p_student) == ft::weak_lock(student)); }) == _students.end())
		{
			std::cout << *ft::weak_lock(p_student) << " was subscribed to " << *this << std::endl;
			_students.push_back(std::move(p_student));
		}
	}
	void unsubscribe(std::weak_ptr<Student> p_student)
	{
		if (ft::erase_if(_students, [&p_student](const std::weak_ptr<Student> &student) { return (ft::weak_lock(p_student) == ft::weak_lock(student)); }))
			std::cout << *ft::weak_lock(p_student) << " was unsubscribed from " << *this << std::endl;
	}
	// getters
	const std::string &name() const { return (_name); }
	std::weak_ptr<Professor> responsible() const { return (_responsible); }
	int classes_to_graduate() const { return (_numberOfClassToGraduate); }
	int capacity() const { return (_maximumNumberOfStudent); }
	std::ostream &print_students(std::ostream &o = std::cout) const;
	bool subscribed_to_by(std::weak_ptr<Student> student)
	{
		return (std::find_if(_students.begin(), _students.end(), [&student](const std::weak_ptr<Student> &s) { return (ft::weak_lock(s) == ft::weak_lock(student)); }) != _students.end());
	}
};

std::ostream &operator<<(std::ostream &o, const Course &c);

#endif
