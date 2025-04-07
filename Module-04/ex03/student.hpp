#ifndef PEOPLE_HPP
# define PEOPLE_HPP

# include "common.hpp"
# include "person.hpp"

class Classroom;

class Student : public Person, public std::enable_shared_from_this<Student>
{
private:
	std::vector<std::weak_ptr<Course>> _subscribedCourses;
	std::weak_ptr<School> _school;

public:
	Student() = default;
	Student(Student&&) = default;
	Student(const Student&) = default;
	Student(const std::string &p_name, std::weak_ptr<School> school) : Person(p_name), _school(std::move(school)) {}
	Student &operator=(const Student&) = default;
	~Student() = default;
	void search_class();
	void attendClass(std::weak_ptr<Classroom> p_classroom);
	void exitClass(std::weak_ptr<Classroom> classroom);
	void graduate(std::weak_ptr<Course> p_course);
	void enroll(std::weak_ptr<Course> course);
	bool studies(std::weak_ptr<Course> course)
	{
		return (ft::weak_ptr_contains(_subscribedCourses, course));
	}
	std::ostream &print_subscribed_courses(std::ostream &o = std::cout) const;
};

std::ostream &operator<<(std::ostream &o, const Student &s);

#endif
