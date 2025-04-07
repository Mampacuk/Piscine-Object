#ifndef SINGLETONS_HPP
# define SINGLETONS_HPP

# include "people.hpp"
# include "courses.hpp"
# include "rooms.hpp"

# include <list>

// only one singleton exists at the time, thanks to hidden constructors,
// providing a unique entry point to its contained object (i.e. the list).
template<class T>
class ListSingleton
{
public:
	static ListSingleton &get()
	{
		static ListSingleton instance;
		return (instance);
	}

	std::list<std::shared_ptr<T>> &access()
	{
		return (_list);
	}

	template<class... Args>
	void emplace_back(Args&&... args)
	{
		_list.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	void push_back(std::shared_ptr<T> value)
	{
		_list.push_back(std::move(value));
	}

	template<class UnaryPredicate>
	std::shared_ptr<T> retrieve(UnaryPredicate pred)
	{
		for (const auto &element : _list)
			if (element && pred(*element))
				return (element);
		return (nullptr);
	}
private:
	ListSingleton() = default;
	ListSingleton(const ListSingleton&) = delete;
	ListSingleton(ListSingleton&&) = delete;
	ListSingleton &operator=(const ListSingleton&) = delete;
	~ListSingleton() = default;

	std::list<std::shared_ptr<T>> _list;
};

using StudentList = ListSingleton<Student>;
using StaffList = ListSingleton<Staff>;
using CourseList = ListSingleton<Course>;
using RoomList = ListSingleton<Room>;

#endif
