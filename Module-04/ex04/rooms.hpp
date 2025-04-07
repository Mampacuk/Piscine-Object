#ifndef ROOMS_HPP
# define ROOMS_HPP

# include "common.hpp"
# include "person.hpp"

class Room : public std::enable_shared_from_this<Room>
{
public:
	using occupants = std::set<std::weak_ptr<Person>, ft::weak_less<Person>>;
private:
	long long ID;
	occupants _occupants;

public:
	Room() = default;
	Room(Room&&) = default;
	Room(const Room&) = default;
	Room(long long id) : ID(id), _occupants() {}
	Room &operator=(const Room&) = default;
	virtual ~Room() = default;

	long long id() const { return (ID); }
	virtual bool canEnter(std::weak_ptr<Person> person) const = 0;
	bool enter(std::weak_ptr<Person> person);
	void exit(std::weak_ptr<Person> person);
	const occupants &get_occupants() const { return (_occupants); }
	bool inside(std::weak_ptr<Person> person)
	{
		return (_occupants.find(person) != _occupants.end());
	}
	std::ostream &print_occupants(std::ostream &o = std::cout) const
	{
		return (ft::print_container(o, _occupants, 
			[](std::ostream &o, const occupants::value_type &ptr) { o << ft::weak_lock(ptr)->name(); }));
	}
};

std::ostream &operator<<(std::ostream &o, const Room &r);

class Classroom : public Room
{
private:
	std::weak_ptr<Course> _currentCourse;

public:
	Classroom() = default;
	Classroom(Classroom&&) = default;
	Classroom(const Classroom&) = default;
	Classroom(long long id) : Room(id) {}
	Classroom &operator=(const Classroom&) = default;
	~Classroom() = default;

	bool canEnter(std::weak_ptr<Person> person) const override;
	void assignCourse(std::weak_ptr<Course> p_course) { _currentCourse = std::move(p_course); }
	std::weak_ptr<Course> current_course() const { return (_currentCourse); }
};

std::ostream &operator<<(std::ostream &o, const Classroom &c);

class SecretarialOffice : public Room
{
public:
	SecretarialOffice() = default;
	SecretarialOffice(SecretarialOffice&&) = default;
	SecretarialOffice(const SecretarialOffice&) = default;
	SecretarialOffice(long long id) : Room(id) {}
	SecretarialOffice &operator=(const SecretarialOffice&) = default;
	~SecretarialOffice() = default;
	
	bool canEnter(std::weak_ptr<Person> person) const override;
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

	bool canEnter(std::weak_ptr<Person> person) const override;
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

	bool canEnter(std::weak_ptr<Person> person) const override;
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

	bool canEnter(std::weak_ptr<Person>) const override { return (true); }
};

std::ostream &operator<<(std::ostream &o, const Courtyard &c);

#endif
