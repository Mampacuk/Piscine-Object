#ifndef PROFESSOR_HPP
# define PROFESSOR_HPP

# include "common.hpp"
# include "staff.hpp"

class Professor : public Staff
{
private:
	std::shared_ptr<Course> _currentCourse;

public:
	Professor() = default;
	Professor(Professor&&) = default;
	Professor(const Professor&) = default;
	Professor(const std::string &p_name) : Staff(p_name) {}
	Professor &operator=(const Professor&) = default;
	~Professor() = default;

	void assignCourse(std::shared_ptr<Course> p_course)
	{
		if (p_course)
		{
			_currentCourse = std::move(p_course);
			std::cout << *this << " was assigned " << *_currentCourse << std::endl;
		}
	}
	// - is called by Headmaster to force professors to do classes.
	// - if professor has no course, they must be provided with a new one.
	// - a professor must find a classroom to hold the class in; if there's no available,
	//   Headmaster should create one.
	void doClass();
	void closeCourse();
	std::shared_ptr<Course> current_course() const { return (_currentCourse); }
};

std::ostream &operator<<(std::ostream &o, const Professor &s);

#endif
