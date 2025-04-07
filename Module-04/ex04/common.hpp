#ifndef COMMON_HPP
# define COMMON_HPP

# include <algorithm>
# include <iostream>
# include <memory>
# include <vector>
# include <string>
# include <functional>
# include <random>
# include <set>

class Course;
std::ostream &operator<<(std::ostream &o, const Course &c);

class Professor;
std::ostream &operator<<(std::ostream &o, const Professor &p);

class Student;
std::ostream &operator<<(std::ostream &o, const Student &s);

class Classroom;
std::ostream &operator<<(std::ostream &o, const Classroom &c);

class Form;
std::ostream &operator<<(std::ostream &o, const Form &f);

class Room;
std::ostream &operator<<(std::ostream &o, const Room &r);

class Person;
std::ostream &operator<<(std::ostream &o, const Person &p);

class Staff;
std::ostream &operator<<(std::ostream &o, const Staff &s);

class Headmaster;
class Secretary;
class School;
class SecretarialOffice;
class HeadmasterOffice;
class StaffRestRoom;
class Courtyard;
class Bell;

enum class FormType;
enum class Event;

namespace ft
{
	template <typename T>
	std::shared_ptr<T> weak_lock(const std::weak_ptr<T> &weak)
	{
		auto shared = weak.lock();
		if (!shared)
			throw std::runtime_error("Attempted to access a null or expired weak_ptr");
		return (shared);
	}

	template <typename Container, typename Printer>
	std::ostream &print_container(std::ostream &o, const Container &container, const Printer &printer)
	{
		const size_t container_size = container.size();
		size_t i = 0;
		o << "{ ";
		for (const auto &element : container)
		{
			printer(o, element);
			if (i != container_size - 1)
				o << ", ";
			i++;
		}
		o << " }";
		return (o);
	}

	template<class T>
	std::ostream &print_shared_ptr(std::ostream &o, const std::shared_ptr<T> &ptr, const std::function<void(std::ostream&, const T&)> &printer = [](std::ostream &o, const T &obj) { o << obj; })
	{
		if (ptr)
			printer(o, *ptr);
		else
			o << "(null)";
		return (o);
	}

	template <template <typename...> class C, typename T>
	std::ostream &print_shared_ptr_container(std::ostream &o, const C<std::shared_ptr<T>> &container, const std::function<void(std::ostream&, const T&)> &printer)
	{
		return (print_container(o, container, [&printer](std::ostream &o, const std::shared_ptr<T> &ptr){ print_shared_ptr(o, ptr, printer); }));
	}

	template <template <typename...> class C, typename T>
	std::ostream &print_weak_ptr_container(std::ostream &o, const C<std::weak_ptr<T>> &container, const std::function<void(std::ostream&, const T&)> &printer)
	{
		return (print_container(o, container, [&printer](std::ostream &o, const std::weak_ptr<T> &ptr){ print_shared_ptr(o, ft::weak_lock(ptr), printer); }));
	}

	template <template <typename...> class C, typename T>
	std::ostream &print_shared_ptr_container_object(std::ostream &o, const C<std::shared_ptr<T>> &container)
	{
		return (print_shared_ptr_container<C, T>(o, container, [](std::ostream &o, const T &val) { o << val; }));
	}
	
	template <template <typename...> class C, typename T, typename Getter>
	std::ostream &print_shared_ptr_container_field(std::ostream &o, const C<std::shared_ptr<T>> &container, const Getter &getter)
	{
		return (print_shared_ptr_container<C, T>(o, container, [&getter](std::ostream &o, const T &val) { o << std::invoke(getter, val); }));
	}

	template <template <typename...> class C, typename T, typename Getter>
	std::ostream &print_weak_ptr_container_field(std::ostream &o, const C<std::weak_ptr<T>> &container, const Getter &getter)
	{
		return (print_weak_ptr_container<C, T>(o, container, [&getter](std::ostream &o, const T &val) { o << std::invoke(getter, val); }));
	}

	template<template <class T, class Alloc> class C, class T, class Alloc, class U = T>
	constexpr typename C<T, Alloc>::size_type erase(C<T, Alloc> &c, const U &value)
	{
		return (erase_if(c, [&value](const T &val) { return (val == value); }));
	}

	template<template <class T, class Alloc> class C, class T, class Alloc, class Pred>
	constexpr typename C<T, Alloc>::size_type erase_if(C<T, Alloc> &c, Pred pred)
	{
		const auto it = std::remove_if(c.begin(), c.end(), pred);
		const auto r = c.end() - it;
		c.erase(it, c.end());
		return (r);
	}

	template <typename T>
	struct weak_less
	{
		bool operator()(const std::weak_ptr<T>& lhs, const std::weak_ptr<T>& rhs) const
		{
			return (weak_lock(lhs) < weak_lock(rhs));
		}
	};

	template <template <typename...> class C, typename T>
	bool weak_ptr_contains(const C<std::weak_ptr<T>> &container, const std::weak_ptr<T> &ptr)
	{
		return (std::find_if(container.begin(), container.end(), [&ptr](const std::weak_ptr<T> &other) { return (weak_lock(ptr) == weak_lock(other)); }) != container.end());
	}

	template <template <typename...> class C, typename T>
	constexpr typename C<T>::size_type weak_ptr_erase(C<std::weak_ptr<T>> &container, const std::weak_ptr<T> &ptr)
	{
		return (erase_if(container, [&ptr](const std::weak_ptr<T> &other) { return (weak_lock(ptr) == weak_lock(other)); }));
	}
}

namespace
{
	std::random_device rd;
	std::mt19937 gen(rd());
}

namespace ft
{
	int generate_int(const int min, const int max);
	std::string select_string(const std::vector<std::string>& strings);

	namespace constants
	{
		inline const std::vector<std::string> cs = {"Data", "Structures", "Algorithms", "Differential",
													"Equations", "Calculus", "Discrete", "Mathematics",
													"Ordinary", "Databases", "Programming", "Machine",
													"Learning", "Numerical", "Analysis", "Optimization"};
		inline const std::vector<std::string> names = {"Marlene", "Henry", "Joel Miller", "Ellie Williams",
													   "Tess Servopoulos", "Abby Anderson", "Owen Moore", "Mel", 
													   "Isaac Dixon", "Nora Harris", "Tommy Miller", "Dina", "Jesse"};
	}
}

#endif
