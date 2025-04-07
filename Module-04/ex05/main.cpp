#include "course.hpp"
#include "school.hpp"
#include "headmaster.hpp"
#include "secretary.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "rooms.hpp"

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

#define EXPECT_FALSE(x) \
	if (x) \
		std::cerr << RED "FAILURE: " RESET #x RED " is not FALSE! " RESET << std::endl; \
	else \
		std::cout << GREEN "SUCCESS: " RESET #x GREEN " is FALSE! " RESET << std::endl;

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
	auto school = std::make_shared<School>();
	school->recruitHeadmaster();
	school->recruitSecretary();
	school->recruitProfessor();
	school->recruitProfessor();
	school->recruitStudent();
	school->recruitStudent();
	school->recruitStudent();
	school->recruitStudent();
	school->recruitStudent();
	school->recruitStudent();
	school->recruitStudent();

	
	school->runDayRoutine();
	
	const auto searched_course = ft::weak_lock(school->getProfessors().back()->current_course());
	const auto found_course = ft::weak_lock(school->getCourse(searched_course->name()));

	EXPECT_EQ(searched_course, found_course)

	school->graduationCeremony();
}
