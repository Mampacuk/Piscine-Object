#ifndef ROOMS_HPP
# define ROOMS_HPP

# include <memory>
# include <vector>

class Course;
class Form;
class Person;

class Room
{
private:
	long long ID;
	std::vector<std::shared_ptr<Person>> _occupants;

public:
	Room();
	bool canEnter(std::shared_ptr<Person>);
	void enter(std::shared_ptr<Person>);
	void exit(std::shared_ptr<Person>);
	
	void printOccupant();
};

class Classroom : public Room
{
private:
	std::shared_ptr<Course> _currentRoom;

public:
	Classroom();
	void assignCourse(std::shared_ptr<Course> p_course);
};

class SecretarialOffice: public Room
{
private:
	std::vector<std::shared_ptr<Form>> _archivedForms;

public:

};

class HeadmasterOffice : public Room
{
private:

public:

};

class StaffRestRoom : public Room
{
private:

public:

};

class Courtyard : public Room
{
private:

public:

};

#endif
