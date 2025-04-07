#include "forms.hpp"
#include "course.hpp"
#include "rooms.hpp"
#include "school.hpp"
#include "professor.hpp"
#include "student.hpp"

void CourseFinishedForm::execute_impl()
{
	auto alumnus = ft::weak_lock(_alumnus);
	auto course = ft::weak_lock(_course);
	std::cout << "Form::execute(): graduated " << alumnus->name() << " from " << course->name() << std::endl;
	alumnus->graduate(_course);
	course->unsubscribe(_alumnus);
}

std::ostream &operator<<(std::ostream &o, const CourseFinishedForm &f)
{
	return (o << "CourseFinished" << static_cast<const Form&>(f) << ")");
}

void NeedMoreClassRoomForm::execute_impl()
{
	auto course = ft::weak_lock(_course);
	auto classroom = ft::weak_lock(ft::weak_lock(_school)->build_room<Classroom>());
	classroom->assignCourse(course);
	std::cout << "Form::execute(): built a classroom with ID=" << classroom->id() << " for course " << course->name() << std::endl;
}

std::ostream &operator<<(std::ostream &o, const NeedMoreClassRoomForm &f)
{
	return (o << "NeedMoreClassRoom" << static_cast<const Form&>(f) << ")");
}

NeedCourseCreationForm::CourseInfo NeedCourseCreationForm::generate_course_info()
{
	return (CourseInfo{ft::select_string(ft::constants::cs) + " " + ft::select_string(ft::constants::cs),
					   ft::generate_int(MIN_CLASSES_TO_GRAD, MAX_CLASSES_TO_GRAD), ft::generate_int(MIN_COURSE_CAPACITY, MAX_COURSE_CAPACITY)});
}

void NeedCourseCreationForm::execute_impl()
{
	const auto course_info = generate_course_info();
	auto professor = ft::weak_lock(_professor);
	auto course = std::make_shared<Course>(course_info.name, course_info.classes_to_graduate, course_info.capacity);
	std::cout << "Form::execute(): created course " << course->name() << " (capacity: " << course->capacity() << ", classes to graduate: " << course->classes_to_graduate() << ") for professor " << professor->name() << std::endl;
	course->assign(_professor);
	professor->assignCourse(course);
}

std::ostream &operator<<(std::ostream &o, const NeedCourseCreationForm &f)
{
	return (o << "NeedCourseCreation" << static_cast<const Form&>(f) << ")");
}

void SubscriptionToCourseForm::execute_impl()
{
	auto course = ft::weak_lock(_course);
	auto student = ft::weak_lock(_student);
	std::cout << "Form::execute(): Student " << student->name() << " enrolled in course " << course->name() << std::endl;
	course->subscribe(student);
	student->enroll(std::move(course));
}

std::ostream &operator<<(std::ostream &o, const SubscriptionToCourseForm &f)
{
	return (o << "SubscriptionToCourse" << static_cast<const Form&>(f) << ")");
}
