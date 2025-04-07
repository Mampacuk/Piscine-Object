#ifndef SCHOOL_HPP
# define SCHOOL_HPP

# include "common.hpp"
# include "observer.hpp"

class School : public std::enable_shared_from_this<School>
{
public:
	using room = std::shared_ptr<Room>;
	using rooms = std::vector<room>;
	using headmaster = std::shared_ptr<Headmaster>;
	using secretary = std::shared_ptr<Secretary>;
	using student = std::shared_ptr<Student>;
	using students = std::vector<student>;
	using professor = std::shared_ptr<Professor>;
	using professors = std::vector<professor>;
private:
	secretary _secretary;
	headmaster _headmaster;
	students _students;
	professors _professors;
	rooms _rooms;

public:
	School();
	School(School&&) = default;
	School(const School&) = default;
	School &operator=(const School&) = default;
	~School() = default;

	template<class RoomType>
	std::weak_ptr<RoomType> build_room()
	{
		auto room = std::make_shared<RoomType>(_rooms.size());
		_rooms.push_back(room);
		return (std::static_pointer_cast<RoomType>(room));
	}
	template<class RoomType>
	std::weak_ptr<RoomType> find_room(std::function<bool(const RoomType&)> predicate = [](const RoomType&) { return (true); })
	{
		if (auto room_it = std::find_if(_rooms.begin(), _rooms.end(),
										[&predicate](const room &room)
										{ auto r = std::dynamic_pointer_cast<RoomType>(room);
										  return (r && predicate(*r));
										});
			room_it != _rooms.end())
			return (std::dynamic_pointer_cast<RoomType>(*room_it));
		return (std::weak_ptr<RoomType>());
	}
	void runDayRoutine();
	void launchClasses();
	void requestRingBell();
	void recruitHeadmaster();
	void recruitSecretary();
	void recruitStudent();
	void recruitProfessor();
	std::weak_ptr<Course> getCourse(std::string p_name) const;
	const students &getStudents() const { return (_students); }
	const professors &getProfessors() const { return (_professors); }
	const rooms &get_rooms() const { return (_rooms); }
	std::weak_ptr<Headmaster> getHeadmaster() const { return (_headmaster); }
	std::weak_ptr<Secretary> getSecretary() const { return (_secretary); }
	void graduationCeremony() const;
private:
	void subscribe_to_bell(std::weak_ptr<Observer> observer);
};

#endif
