#include "common.hpp"
#include "singletons.hpp"

#include <iostream>

#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_MAGENTA "\033[95m"

#define EXPECT_EQ(x, y) \
	if (!(x == y)) \
		std::cerr << RED "FAILURE: " RESET #x RED " != " RESET #y << std::endl; \
	else \
		std::cout << GREEN "SUCCESS: " RESET #x GREEN " == " RESET #y << std::endl;

#define EXPECT_TRUE(x) \
	if (!x) \
		std::cerr << RED "FAILURE: " RESET #x RED " is not TRUE! " RESET << std::endl; \
	else \
		std::cout << GREEN "SUCCESS: " RESET #x GREEN " is TRUE! " RESET << std::endl;

#define EXPECT_THROW(x) try \
{ \
	x; \
	std::cerr << RED "FAILURE: " RESET #x RED " didn't throw!" RESET << std::endl; \
} \
catch (const std::exception &e) \
{ \
	std::cout << GREEN "SUCCESS: caught an exception from " RESET #x GREEN ": " << e.what() << RESET << std::endl; \
}

#define EXPECT_NO_THROW(x) try \
{ \
	x; \
	std::cout << GREEN "SUCCESS: " RESET #x GREEN " didn't throw!" RESET << std::endl; \
} \
catch (const std::exception &e) \
{ \
	std::cerr << RED "FAILURE: caught an exception from " RESET #x RED ": " << e.what() << RESET << std::endl; \
}

#define PRINT_TEST_CASE(suite, test) std::cout << BRIGHT_MAGENTA suite " : " BRIGHT_CYAN test RESET << std::endl;

int main()
{
	StudentList &students = StudentList::get();
	StaffList &staff = StaffList::get();
	CourseList &courses = CourseList::get();
	RoomList &rooms = RoomList::get();

	EXPECT_TRUE(students.access().empty())
	EXPECT_TRUE(staff.access().empty())
	EXPECT_TRUE(courses.access().empty())
	EXPECT_TRUE(rooms.access().empty())

	students.emplace_back("Harry");
	staff.emplace_back("James");
	staff.push_back(std::make_shared<Headmaster>("Laura"));
	staff.push_back(std::make_shared<Secretary>("Angela"));
	staff.push_back(std::make_shared<Professor>("Eddie"));
	courses.emplace_back("Data Structures", 1, 2);
	rooms.emplace_back(0);
	rooms.push_back(std::make_shared<Classroom>(1));
	rooms.push_back(std::make_shared<SecretarialOffice>(2));
	rooms.push_back(std::make_shared<HeadmasterOffice>(3));
	rooms.push_back(std::make_shared<StaffRestRoom>(4));
	rooms.push_back(std::make_shared<Courtyard>(5));

	EXPECT_TRUE(!students.access().empty())
	EXPECT_TRUE(!staff.access().empty())
	EXPECT_TRUE(!courses.access().empty())
	EXPECT_TRUE(!rooms.access().empty())

	ft::print_shared_ptr_member(std::cout, students.retrieve([](const Student &s){ return (s.name() == "Harry"); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, students.retrieve([](const Student &s){ return (s.name() == "Pyramid Head"); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, staff.retrieve([](const Staff &s){ return (dynamic_cast<const Headmaster*>(&s)); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, staff.retrieve([](const Staff &s){ return (dynamic_cast<const Secretary*>(&s)); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, staff.retrieve([](const Staff &s){ return (dynamic_cast<const Professor*>(&s)); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, courses.retrieve([](const Course &c){ return (c.name() == "Data Structures"); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, rooms.retrieve([](const Room &r){ return (r.id() == 0); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, rooms.retrieve([](const Room &r){ return (dynamic_cast<const Classroom*>(&r)); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, rooms.retrieve([](const Room &r){ return (dynamic_cast<const SecretarialOffice*>(&r)); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, rooms.retrieve([](const Room &r){ return (dynamic_cast<const HeadmasterOffice*>(&r)); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, rooms.retrieve([](const Room &r){ return (dynamic_cast<const StaffRestRoom*>(&r)); }));
	std::cout << std::endl;
	ft::print_shared_ptr_member(std::cout, rooms.retrieve([](const Room &r){ return (dynamic_cast<const Courtyard*>(&r)); }));
	std::cout << std::endl;
}
