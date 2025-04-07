#ifndef PEOPLE_HPP
# define PEOPLE_HPP

# include "common.hpp"
# include "forms.hpp"
# include <string>
# include <vector>
# include <list>

class Course;
class Classroom;
class Room;

class Person
{
private:
	std::string _name;
	std::shared_ptr<Room> _currentRoom;
public:
	Person() = default;
	Person(Person&&) = default;
	Person(const Person&) = default;
	Person(const std::string &p_name) : _name(p_name), _currentRoom() {}
	Person &operator=(const Person&) = default;
	virtual ~Person() = default;

	const std::string &name() const { return (_name); }
	std::shared_ptr<Room> room() const { return (_currentRoom); }
};

std::ostream &operator<<(std::ostream &o, const Person &p)
{
	o << "Person(name: " << p.name() <<  ", currentRoom: ";
	return (ft::print_shared_ptr_member(o, p.room()) << ")");
}

class Staff : public Person
{
private:

public:
	Staff() = default;
	Staff(Staff&&) = default;
	Staff(const Staff&) = default;
	Staff(const std::string &p_name) : Person(p_name) {}
	Staff &operator=(const Staff&) = default;
	~Staff() = default;

	void sign(std::shared_ptr<Form> p_form);
};

std::ostream &operator<<(std::ostream &o, const Staff &s)
{
	return (o << "Staff(" << static_cast<const Person&>(s) << ")");
}

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
	void graduate(std::shared_ptr<Course> p_course);
	std::ostream &printSubscribedCourses(std::ostream &o = std::cout) const { return (ft::print_shared_ptr_container(o, _subscribedCourses)); }
};

std::ostream &operator<<(std::ostream &o, const Student &s)
{
	o << "Student(subscribedCourses: ";
	return (s.printSubscribedCourses(o) << ", " << static_cast<const Person&>(s) << ")");
}

class Headmaster : public Staff
{
private:
	std::vector<std::shared_ptr<Form>> _formToValidate;
	
public:
	Headmaster() = default;
	Headmaster(Headmaster&&) = default;
	Headmaster(const Headmaster&) = default;
	Headmaster(const std::string &p_name) : Staff(p_name) {}
	Headmaster &operator=(const Headmaster&) = default;
	~Headmaster() = default;


	void receiveForm(std::shared_ptr<Form> p_form) { _formToValidate.push_back(std::move(p_form)); }
	std::ostream &printFormsToValidate(std::ostream &o = std::cout) const { return (ft::print_shared_ptr_container(o, _formToValidate)); }
};

std::ostream &operator<<(std::ostream &o, const Headmaster &h)
{
	o << "Headmaster(formToValidate: ";
	return (h.printFormsToValidate(o) << ", " << static_cast<const Staff&>(h) << ")");
}

class Secretary : public Staff
{
private:

public:
	Secretary() = default;
	Secretary(Secretary&&) = default;
	Secretary(const Secretary&) = default;
	Secretary(const std::string &p_name) : Staff(p_name) {}
	Secretary &operator=(const Secretary&) = default;
	~Secretary() = default;

	std::shared_ptr<Form> createForm(FormType p_formType);
	void archiveForm();
};

std::ostream &operator<<(std::ostream &o, const Secretary &s)
{
	return (o << "Secretary(" << static_cast<const Staff&>(s) << ")");
}

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

	void assignCourse(std::shared_ptr<Course> p_course) { _currentCourse = std::move(p_course); }
	void doClass();
	void closeCourse();
	std::shared_ptr<Course> current_course() const { return (_currentCourse); }
};

std::ostream &operator<<(std::ostream &o, const Professor &s)
{
	o << "Professor(currentCourse: ";
	return (ft::print_shared_ptr_member(o, s.current_course()) << ", " << static_cast<const Staff&>(s) << ")");
}

#endif
