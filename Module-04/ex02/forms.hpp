#ifndef FORMS_HPP
# define FORMS_HPP

# define MIN_CLASSES_TO_GRAD 3
# define MAX_CLASSES_TO_GRAD 10

# define MIN_COURSE_CAPACITY 5
# define MAX_COURSE_CAPACITY 15

# include "common.hpp"
# include "course.hpp"
# include "form.hpp"
# include "form_type.hpp"
# include "rooms.hpp"
# include "school.hpp"
# include "professor.hpp"
# include "student.hpp"

class CourseFinishedForm : public Form
{
private:
	std::shared_ptr<Student> _alumnus;
	std::shared_ptr<Course> _course;
public:
	CourseFinishedForm() : Form(FormType::CourseFinished), _alumnus(), _course() {}
	CourseFinishedForm(CourseFinishedForm&&) = delete;
	CourseFinishedForm(const CourseFinishedForm&) = delete;
	CourseFinishedForm &operator=(const CourseFinishedForm&) = delete;
	~CourseFinishedForm() = default;

	void set_course(std::shared_ptr<Course> course) { _course = std::move(course); }
	void set_alumnus(std::shared_ptr<Student> student) { _alumnus = std::move(student); }
	bool is_complete() const override { return (_course && _alumnus); }
private:
	void execute_impl() override
	{
		std::cout << "Form::execute(): graduated " << *_alumnus << " from " << *_course << std::endl;
		_alumnus->graduate(_course);
		_course->unsubscribe(_alumnus);
	}
};

std::ostream &operator<<(std::ostream &o, const CourseFinishedForm &f);

class NeedMoreClassRoomForm : public Form
{
private:
	std::shared_ptr<Course> _course;
	std::shared_ptr<School> _school;
public:
	NeedMoreClassRoomForm() : Form(FormType::NeedMoreClassRoom) {}
	NeedMoreClassRoomForm(NeedMoreClassRoomForm&&) = delete;
	NeedMoreClassRoomForm(const NeedMoreClassRoomForm&) = delete;
	NeedMoreClassRoomForm &operator=(const NeedMoreClassRoomForm&) = delete;
	~NeedMoreClassRoomForm() = default;

	void set_school(std::shared_ptr<School> school) { _school = std::move(school); }
	void set_course(std::shared_ptr<Course> course) { _course = std::move(course); }
	bool is_complete() const override { return (_course && _school); }
private:
	void execute_impl() override
	{
		auto classroom = _school->build_room<Classroom>();
		std::cout << "Form::execute(): built a " << *classroom << " for " << *_course << std::endl;
		classroom->assignCourse(std::move(_course));
	}
};

std::ostream &operator<<(std::ostream &o, const NeedMoreClassRoomForm &f);

class NeedCourseCreationForm : public Form
{
private:
	struct CourseInfo
	{
		std::string name;
		int classes_to_graduate;
		int capacity;
	};
	std::shared_ptr<Professor> _professor;
public:
	NeedCourseCreationForm() : Form(FormType::NeedCourseCreation) {}
	NeedCourseCreationForm(NeedCourseCreationForm&&) = delete;
	NeedCourseCreationForm(const NeedCourseCreationForm&) = delete;
	NeedCourseCreationForm &operator=(const NeedCourseCreationForm&) = delete;
	~NeedCourseCreationForm() = default;
	
	void set_professor(std::shared_ptr<Professor> professor) { _professor = std::move(professor); }
	bool is_complete() const override { return (static_cast<bool>(_professor)); }
private:
	static CourseInfo generate_course_info();
	void execute_impl() override;
};

std::ostream &operator<<(std::ostream &o, const NeedCourseCreationForm &f);

class SubscriptionToCourseForm : public Form
{
private:
	std::shared_ptr<Student> _student;
	std::shared_ptr<Course> _course;
public:
	SubscriptionToCourseForm() : Form(FormType::SubscriptionToCourse) {}
	SubscriptionToCourseForm(SubscriptionToCourseForm&&) = delete;
	SubscriptionToCourseForm(const SubscriptionToCourseForm&) = delete;
	SubscriptionToCourseForm &operator=(const SubscriptionToCourseForm&) = delete;
	~SubscriptionToCourseForm() = default;

	void set_student(std::shared_ptr<Student> student) { _student = std::move(student); }
	void set_course(std::shared_ptr<Course> course) { _course = std::move(course); }
	bool is_complete() const override { return (_student && _course); }
private:
	void execute_impl() override
	{
		std::cout << "Form::execute(): " << *_student << " enrolled in " << *_course << std::endl;
		_course->subscribe(_student);
		_student->enroll(std::move(_course));
	}
};

std::ostream &operator<<(std::ostream &o, const SubscriptionToCourseForm &f);

#endif
