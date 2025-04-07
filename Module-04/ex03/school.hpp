#ifndef SCHOOL_HPP
# define SCHOOL_HPP

# include "common.hpp"

class School : public std::enable_shared_from_this<School>
{
public:
	using rooms = std::vector<std::shared_ptr<Room>>;
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
	School() : _secretary(), _headmaster(), _students(), _professors(), _rooms() {};
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
};

#endif
