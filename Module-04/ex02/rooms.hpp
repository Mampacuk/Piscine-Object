#ifndef ROOMS_HPP
# define ROOMS_HPP

# include "common.hpp"
# include "person.hpp"

class Room
{
private:
	long long ID;
	std::vector<std::shared_ptr<Person>> _occupants;

public:
	Room() = default;
	Room(Room&&) = default;
	Room(const Room&) = default;
	Room(long long id) : ID(id), _occupants() {}
	Room &operator=(const Room&) = default;
	virtual ~Room() = default;

	long long id() const { return (ID); }
	bool canEnter(std::shared_ptr<Person> person) const;
	void enter(std::shared_ptr<Person> person) { if (canEnter(person)) _occupants.push_back(std::move(person)); }
	void exit(std::shared_ptr<Person> person) { ft::erase(_occupants, std::move(person)); }
	std::ostream &print_occupants(std::ostream &o = std::cout) const { return (ft::print_shared_ptr_container_field(o, _occupants, Person::name)); }
};

std::ostream &operator<<(std::ostream &o, const Room &r);

class Classroom : public Room
{
private:
	std::shared_ptr<Course> _currentCourse;

public:
	Classroom() = default;
	Classroom(Classroom&&) = default;
	Classroom(const Classroom&) = default;
	Classroom(long long id) : Room(id) {}
	Classroom &operator=(const Classroom&) = default;
	~Classroom() = default;

	void assignCourse(std::shared_ptr<Course> p_course) { _currentCourse = std::move(p_course); }
	std::shared_ptr<Course> current_course() const { return (_currentCourse); }
};

std::ostream &operator<<(std::ostream &o, const Classroom &c);

class SecretarialOffice : public Room
{
private:
	std::vector<std::shared_ptr<Form>> _archivedForms;

public:
	SecretarialOffice() = default;
	SecretarialOffice(SecretarialOffice&&) = default;
	SecretarialOffice(const SecretarialOffice&) = default;
	SecretarialOffice(long long id) : Room(id) {}
	SecretarialOffice &operator=(const SecretarialOffice&) = default;
	~SecretarialOffice() = default;

	std::ostream &printArchivedForms(std::ostream &o = std::cout) const { return (ft::print_shared_ptr_container_object(o, _archivedForms)); }
};

std::ostream &operator<<(std::ostream &o, const SecretarialOffice &s);

class HeadmasterOffice : public Room
{
private:

public:
	HeadmasterOffice() = default;
	HeadmasterOffice(HeadmasterOffice&&) = default;
	HeadmasterOffice(const HeadmasterOffice&) = default;
	HeadmasterOffice(long long id) : Room(id) {}
	HeadmasterOffice &operator=(const HeadmasterOffice&) = default;
	~HeadmasterOffice() = default;
};

std::ostream &operator<<(std::ostream &o, const HeadmasterOffice &h);

class StaffRestRoom : public Room
{
private:

public:
	StaffRestRoom() = default;
	StaffRestRoom(StaffRestRoom&&) = default;
	StaffRestRoom(const StaffRestRoom&) = default;
	StaffRestRoom(long long id) : Room(id) {}
	StaffRestRoom &operator=(const StaffRestRoom&) = default;
	~StaffRestRoom() = default;
};

std::ostream &operator<<(std::ostream &o, const StaffRestRoom &s);

class Courtyard : public Room
{
private:

public:
	Courtyard() = default;
	Courtyard(Courtyard&&) = default;
	Courtyard(const Courtyard&) = default;
	Courtyard(long long id) : Room(id) {}
	Courtyard &operator=(const Courtyard&) = default;
	~Courtyard() = default;
};

std::ostream &operator<<(std::ostream &o, const Courtyard &c);

#endif
