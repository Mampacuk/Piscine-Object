#include "common.hpp"
#include "staff.hpp"
#include "professor.hpp"
#include "headmaster.hpp"
#include "secretary.hpp"
#include "forms.hpp"
#include "school.hpp"

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
	auto professor = std::make_shared<Professor>("Marlene");
	auto student = std::make_shared<Student>("Henry"); 
	auto secretary = std::make_shared<Secretary>("Joel Miller");
	auto headmaster = std::make_shared<Headmaster>("Ellie Williams");
	auto staff = std::make_shared<Staff>("Tess Servopoulos");

	PRINT_TEST_CASE("NEED COURSE CREATION", "NeedCourseCreationForm")
	// NEED COURSE CREATION
	auto need_course_creation = std::static_pointer_cast<NeedCourseCreationForm>(secretary->createForm(FormType::NeedCourseCreation));
	EXPECT_TRUE(need_course_creation)
	EXPECT_FALSE(need_course_creation->is_complete())
	EXPECT_FALSE(staff->sign(need_course_creation))
	EXPECT_FALSE(secretary->sign(need_course_creation))
	EXPECT_FALSE(headmaster->sign(need_course_creation))
	EXPECT_FALSE(need_course_creation->execute())
	
	need_course_creation->set_professor(professor);

	EXPECT_TRUE(need_course_creation->is_complete())
	EXPECT_TRUE(headmaster->sign(need_course_creation))
	EXPECT_FALSE(professor->current_course())
	EXPECT_TRUE(need_course_creation->execute())
	EXPECT_TRUE(professor->current_course())
	EXPECT_EQ(professor->current_course()->responsible().lock(), professor)

	const auto marlenes_course = professor->current_course();

	PRINT_TEST_CASE("COURSE SUBSCRIPTION", "SubscriptionToCourseForm")
	// COURSE SUBSCRIPTION
	auto course_subscription = std::static_pointer_cast<SubscriptionToCourseForm>(secretary->createForm(FormType::SubscriptionToCourse));
	EXPECT_FALSE(course_subscription->is_complete())
	course_subscription->set_course(marlenes_course);
	EXPECT_FALSE(course_subscription->is_complete())
	course_subscription->set_student(student);
	EXPECT_TRUE(course_subscription->is_complete())
	headmaster->sign(course_subscription);
	course_subscription->execute();
	EXPECT_TRUE(student->studies(marlenes_course))
	EXPECT_TRUE(marlenes_course->subscribed_to_by(student))

	PRINT_TEST_CASE("NEED MORE CLASSROOMS", "NeedMoreClassRoomForm")
	// NEED MORE CLASSROOMS
	auto need_more_classroom = std::static_pointer_cast<NeedMoreClassRoomForm>(secretary->createForm(FormType::NeedMoreClassRoom));
	auto school = std::make_shared<School>();
	EXPECT_TRUE(school->get_rooms().empty())
	EXPECT_FALSE(need_more_classroom->is_complete())
	need_more_classroom->set_school(school);
	EXPECT_FALSE(need_more_classroom->is_complete())
	need_more_classroom->set_course(marlenes_course);
	EXPECT_TRUE(need_more_classroom->is_complete())
	EXPECT_TRUE(headmaster->sign(need_more_classroom));
	EXPECT_TRUE(need_more_classroom->execute());
	EXPECT_FALSE(school->get_rooms().empty())
	EXPECT_EQ(static_cast<const Classroom&>(*school->get_rooms().at(0)).current_course(), marlenes_course);

	PRINT_TEST_CASE("COURSE FINISHED", "CourseFinishedForm")
	// COURSE FINISHED
	auto course_finished = std::static_pointer_cast<CourseFinishedForm>(secretary->createForm(FormType::CourseFinished));
	EXPECT_FALSE(course_finished->is_complete())
	course_finished->set_alumnus(student);
	EXPECT_FALSE(course_finished->is_complete())
	course_finished->set_course(marlenes_course);
	EXPECT_TRUE(course_finished->is_complete())
	EXPECT_TRUE(headmaster->sign(course_finished));
	EXPECT_TRUE(course_finished->execute());
	EXPECT_FALSE(marlenes_course->subscribed_to_by(student))
	EXPECT_FALSE(student->studies(marlenes_course));
}
