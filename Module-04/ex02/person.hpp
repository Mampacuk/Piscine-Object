#ifndef PERSON_HPP
# define PERSON_HPP

# include "common.hpp"

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

std::ostream &operator<<(std::ostream &o, const Person &p);

#endif
