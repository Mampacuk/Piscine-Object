#include "forms.hpp"

#include <random>

NeedCourseCreationForm::CourseInfo NeedCourseCreationForm::generate_course_info()
{
	static const std::vector<std::string> cs = {"Data", "Structures", "Algorithms", "Differential",
												"Equations", "Calculus", "Discrete", "Mathematics",
												"Ordinary", "Databases", "Programming", "Machine",
												"Learning", "Numerical", "Analysis", "Optimization"};
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> name_dist1(0, cs.size());
	static std::uniform_int_distribution<> name_dist2(0, cs.size() - 1);
	static std::uniform_int_distribution<> class_to_grad_dist(MIN_CLASSES_TO_GRAD, MAX_CLASSES_TO_GRAD);
	static std::uniform_int_distribution<> capacity_dist(MIN_COURSE_CAPACITY, MAX_COURSE_CAPACITY);
	int i1 = name_dist1(gen);
	int i2 = name_dist2(gen);
	if (i2 >= i1)
		i2++;
	return (CourseInfo{cs[i1] + " " + cs[i2], class_to_grad_dist(gen), capacity_dist(gen)});
}

void NeedCourseCreationForm::execute_impl()
{
	const auto course_info = generate_course_info();
	auto course = std::make_shared<Course>(course_info.name, course_info.classes_to_graduate, course_info.capacity);
	std::cout << "Form::execute(): created " << *course << " for " << *_professor << std::endl;
	course->assign(_professor);
	_professor->assignCourse(course);
}

std::ostream &operator<<(std::ostream &o, const CourseFinishedForm &f)
{
	return (o << "CourseFinished" << static_cast<const Form&>(f) << ")");
}

std::ostream &operator<<(std::ostream &o, const NeedMoreClassRoomForm &f)
{
	return (o << "NeedMoreClassRoom" << static_cast<const Form&>(f) << ")");
}

std::ostream &operator<<(std::ostream &o, const NeedCourseCreationForm &f)
{
	return (o << "NeedCourseCreation" << static_cast<const Form&>(f) << ")");
}

std::ostream &operator<<(std::ostream &o, const SubscriptionToCourseForm &f)
{
	return (o << "SubscriptionToCourse" << static_cast<const Form&>(f) << ")");
}
