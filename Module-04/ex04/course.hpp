#ifndef COURSES_HPP
# define COURSES_HPP

# include "common.hpp"

# include <map>

# define MIN_CLASSES_TO_GRAD 3
# define MAX_CLASSES_TO_GRAD 5

# define MIN_COURSE_CAPACITY 3
# define MAX_COURSE_CAPACITY 5

class Course
{
public:
	using attendance = std::map<std::weak_ptr<Student>, unsigned int, ft::weak_less<Student>>;
private:
	std::string _name;
	std::weak_ptr<Professor> _responsible;
	attendance _attendance;
	unsigned int _numberOfClassToGraduate;
	unsigned int _maximumNumberOfStudent;
	size_t _id;

	static size_t _global_id;
public:
	Course() = default;
	Course(Course&&) = default;
	Course(const Course&) = default;
	Course(const std::string &name, int num_class_to_graduate = 0, int max_num_students = 0) : _name(name), _responsible(),
		_attendance(), _numberOfClassToGraduate(num_class_to_graduate), _maximumNumberOfStudent(max_num_students), _id(_global_id++) {}
	Course &operator=(const Course&) = default;
	~Course() {}
	// setters
	void assign(std::weak_ptr<Professor> p_professor);
	void subscribe(std::weak_ptr<Student> p_student);
	void unsubscribe(std::weak_ptr<Student> p_student);
	// getters
	std::string name() const { return ("\"" + _name + "\"(" + std::to_string(_id) + ")"); }
	std::weak_ptr<Professor> responsible() const { return (_responsible); }
	unsigned int classes_to_graduate() const { return (_numberOfClassToGraduate); }
	unsigned int capacity() const { return (_maximumNumberOfStudent); }
	std::ostream &print_students(std::ostream &o = std::cout) const;
	bool subscribed_to_by(std::weak_ptr<Student> student)
	{
		return (_attendance.find(student) != _attendance.end());
	}
	const attendance &get_attendance() const { return (_attendance); };
	void mark_attendance(std::weak_ptr<Student> student);
};

std::ostream &operator<<(std::ostream &o, const Course &c);

#endif
