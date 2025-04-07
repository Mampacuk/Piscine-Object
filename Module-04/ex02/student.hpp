#ifndef PEOPLE_HPP
# define PEOPLE_HPP

# include "common.hpp"
# include "person.hpp"

class Classroom;

class Student : public Person
{
private:
	std::vector<std::shared_ptr<Course>> _subscribedCourses;

public:
	Student() = default;
	Student(Student&&) = default;
	Student(const Student&) = default;
	Student(const std::string &p_name) : Person(p_name) {}
	Student &operator=(const Student&) = default;
	~Student() = default;
	void attendClass(std::shared_ptr<Classroom> p_classroom);
	void exitClass();
	void graduate(std::shared_ptr<Course> p_course)
	{
		if (p_course && ft::erase(_subscribedCourses, p_course))
				std::cout << *this << " graduated from " << *p_course << std::endl;
	}
	void enroll(std::shared_ptr<Course> course)
	{
		if (course && std::find(_subscribedCourses.begin(), _subscribedCourses.end(), course) == _subscribedCourses.end())
		{
			std::cout << *this << " enrolled in " << *course << std::endl;
			_subscribedCourses.push_back(std::move(course));
		}
	}
	bool studies(std::shared_ptr<Course> course)
	{
		return (std::find(_subscribedCourses.begin(), _subscribedCourses.end(), course) != _subscribedCourses.end());
	}
	std::ostream &print_subscribed_courses(std::ostream &o = std::cout) const;
};

std::ostream &operator<<(std::ostream &o, const Student &s);

#endif
