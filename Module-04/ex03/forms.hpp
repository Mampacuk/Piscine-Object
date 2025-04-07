#ifndef FORMS_HPP
# define FORMS_HPP

# include "common.hpp"
# include "form.hpp"
# include "form_type.hpp"

class CourseFinishedForm : public Form
{
private:
	std::weak_ptr<Student> _alumnus;
	std::weak_ptr<Course> _course;
public:
	CourseFinishedForm() : Form(FormType::CourseFinished), _alumnus(), _course() {}
	CourseFinishedForm(CourseFinishedForm&&) = delete;
	CourseFinishedForm(const CourseFinishedForm&) = delete;
	CourseFinishedForm &operator=(const CourseFinishedForm&) = delete;
	~CourseFinishedForm() = default;

	void set_course(std::weak_ptr<Course> course) { _course = std::move(course); }
	void set_alumnus(std::weak_ptr<Student> student) { _alumnus = std::move(student); }
	bool is_complete() const override { return (ft::weak_lock(_course) && ft::weak_lock(_alumnus)); }
private:
	void execute_impl() override;
};

std::ostream &operator<<(std::ostream &o, const CourseFinishedForm &f);

class NeedMoreClassRoomForm : public Form
{
private:
	std::weak_ptr<Course> _course;
	std::weak_ptr<School> _school;
public:
	NeedMoreClassRoomForm() : Form(FormType::NeedMoreClassRoom) {}
	NeedMoreClassRoomForm(NeedMoreClassRoomForm&&) = delete;
	NeedMoreClassRoomForm(const NeedMoreClassRoomForm&) = delete;
	NeedMoreClassRoomForm &operator=(const NeedMoreClassRoomForm&) = delete;
	~NeedMoreClassRoomForm() = default;

	void set_school(std::weak_ptr<School> school) { _school = std::move(school); }
	void set_course(std::weak_ptr<Course> course) { _course = std::move(course); }
	bool is_complete() const override { return (ft::weak_lock(_course) && ft::weak_lock(_school)); }
private:
	void execute_impl() override;
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
	std::weak_ptr<Professor> _professor;
public:
	NeedCourseCreationForm() : Form(FormType::NeedCourseCreation) {}
	NeedCourseCreationForm(NeedCourseCreationForm&&) = delete;
	NeedCourseCreationForm(const NeedCourseCreationForm&) = delete;
	NeedCourseCreationForm &operator=(const NeedCourseCreationForm&) = delete;
	~NeedCourseCreationForm() = default;
	
	void set_professor(std::weak_ptr<Professor> professor) { _professor = std::move(professor); }
	bool is_complete() const override { return (static_cast<bool>(ft::weak_lock(_professor))); }
private:
	static CourseInfo generate_course_info();
	void execute_impl() override;
};

std::ostream &operator<<(std::ostream &o, const NeedCourseCreationForm &f);

class SubscriptionToCourseForm : public Form
{
private:
	std::weak_ptr<Student> _student;
	std::weak_ptr<Course> _course;
public:
	SubscriptionToCourseForm() : Form(FormType::SubscriptionToCourse) {}
	SubscriptionToCourseForm(SubscriptionToCourseForm&&) = delete;
	SubscriptionToCourseForm(const SubscriptionToCourseForm&) = delete;
	SubscriptionToCourseForm &operator=(const SubscriptionToCourseForm&) = delete;
	~SubscriptionToCourseForm() = default;

	void set_student(std::weak_ptr<Student> student) { _student = std::move(student); }
	void set_course(std::weak_ptr<Course> course) { _course = std::move(course); }
	bool is_complete() const override { return (ft::weak_lock(_student) && ft::weak_lock(_course)); }
private:
	void execute_impl() override;
};

std::ostream &operator<<(std::ostream &o, const SubscriptionToCourseForm &f);

#endif
