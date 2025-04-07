#ifndef PROFESSOR_HPP
# define PROFESSOR_HPP

# include "common.hpp"
# include "staff.hpp"

class Professor : public Staff, public std::enable_shared_from_this<Professor>
{
private:
	std::shared_ptr<Course> _currentCourse;
	std::weak_ptr<School> _school;

public:
	Professor() = default;
	Professor(Professor&&) = default;
	Professor(const Professor&) = default;
	Professor(const std::string &p_name, std::weak_ptr<School> school) : Staff(p_name), _school(std::move(school)) {}
	Professor &operator=(const Professor&) = default;
	~Professor() = default;

	void acquire_course();
	void assignCourse(std::shared_ptr<Course> p_course);
	void doClass();
	void closeCourse() const;
	std::weak_ptr<Course> current_course() const { return (_currentCourse); }
};

std::ostream &operator<<(std::ostream &o, const Professor &s);

#endif
