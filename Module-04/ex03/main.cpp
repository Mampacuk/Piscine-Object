#include "course.hpp"
#include "school.hpp"
#include "headmaster.hpp"

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
	for (size_t i = 0; i < MAX_COURSE_CAPACITY + 2; i++)
		school->recruitStudent();
	const auto headmaster = ft::weak_lock(school->getHeadmaster());
	for (size_t i = 0; i < MAX_CLASSES_TO_GRAD + 1; i++)
		headmaster->make_professors_do_class();
}
