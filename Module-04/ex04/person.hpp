#ifndef PERSON_HPP
# define PERSON_HPP

# include "common.hpp"

class Person
{
private:
	std::string _name;
	size_t _id;
	std::weak_ptr<Room> _currentRoom;
	
	static size_t _global_id;
public:
	Person() = default;
	Person(Person&&) = default;
	Person(const Person&) = default;
	Person(const std::string &p_name) : _name(p_name), _id(_global_id++), _currentRoom() { }
	Person &operator=(const Person&) = default;
	virtual ~Person() = default;

	std::string name() const { return (_name + "(" + std::to_string(_id)) + ")"; }
	std::weak_ptr<Room> room() const { return (_currentRoom); }
	void set_room(std::weak_ptr<Room> room) { _currentRoom = std::move(room); }
	template <class RoomType>
	bool in_room() const
	{
		return (std::dynamic_pointer_cast<RoomType>(_currentRoom.lock()).get());
	}
};

std::ostream &operator<<(std::ostream &o, const Person &p);

#endif
