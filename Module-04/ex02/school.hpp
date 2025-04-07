#ifndef SCHOOL_HPP
# define SCHOOL_HPP

# include "common.hpp"

class School
{
public:
	using rooms = std::vector<std::shared_ptr<Room>>;
private:
	size_t _next_room_id;
	rooms _rooms;
public:
	School() = default;
	School(School&&) = default;
	School(const School&) = default;
	School &operator=(const School&) = default;
	~School() = default;

	template<class RoomType>
	std::shared_ptr<RoomType> build_room()
	{
		std::shared_ptr<Room> room = std::make_shared<RoomType>(_next_room_id++);
		_rooms.push_back(room);
		return (std::static_pointer_cast<RoomType>(room));
	}
	rooms get_rooms() const { return (_rooms); }
};

#endif
