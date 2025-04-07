#ifndef FORMS_HPP
# define FORMS_HPP

# include <iostream>

enum class FormType
{
	CourseFinished,
	NeedMoreClassRoom,
	NeedCourseCreation,
	SubscriptionToCourse
};

namespace
{
	const char *g_form_type_strs[] = {"CourseFinished", "NeedMoreClassRoom", "NeedCourseCreation", "SubscriptionToCourse"};
}

class Form
{
private:
	FormType _formType;

public:
	Form() = default;
	Form(Form&&) = default;
	Form(const Form&) = default;
	Form(FormType p_formType) : _formType(p_formType) {}
	Form &operator=(const Form&) = default;
	virtual ~Form() = default;

	virtual void execute() = 0;
	FormType form_type() const { return (_formType); }
};

std::ostream &operator<<(std::ostream &o, const Form &f)
{
	return (o << "Form(formType: " << g_form_type_strs[static_cast<int>(f.form_type())] << ")");
}

class CourseFinishedForm : public Form
{
private:

public:
	CourseFinishedForm() : Form(FormType::CourseFinished) {}
	CourseFinishedForm(CourseFinishedForm&&) = delete;
	CourseFinishedForm(const CourseFinishedForm&) = delete;
	CourseFinishedForm &operator=(const CourseFinishedForm&) = delete;
	~CourseFinishedForm() = default;

	void execute() override;
};

std::ostream &operator<<(std::ostream &o, const CourseFinishedForm &f)
{
	return (o << "CourseFinishedForm(" << static_cast<const Form&>(f) << ")");
}

class NeedMoreClassRoomForm : public Form
{
private:

public:
	NeedMoreClassRoomForm() : Form(FormType::NeedMoreClassRoom) {}
	NeedMoreClassRoomForm(NeedMoreClassRoomForm&&) = delete;
	NeedMoreClassRoomForm(const NeedMoreClassRoomForm&) = delete;
	NeedMoreClassRoomForm &operator=(const NeedMoreClassRoomForm&) = delete;
	~NeedMoreClassRoomForm() = default;

	void execute() override;
};

std::ostream &operator<<(std::ostream &o, const NeedMoreClassRoomForm &f)
{
	return (o << "NeedMoreClassRoomForm(" << static_cast<const Form&>(f) << ")");
}

class NeedCourseCreationForm : public Form
{
private:

public:
	NeedCourseCreationForm() : Form(FormType::NeedCourseCreation) {}
	NeedCourseCreationForm(NeedCourseCreationForm&&) = delete;
	NeedCourseCreationForm(const NeedCourseCreationForm&) = delete;
	NeedCourseCreationForm &operator=(const NeedCourseCreationForm&) = delete;
	~NeedCourseCreationForm() = default;

	void execute() override;
};

std::ostream &operator<<(std::ostream &o, const NeedCourseCreationForm &f)
{
	return (o << "NeedCourseCreationForm(" << static_cast<const Form&>(f) << ")");
}

class SubscriptionToCourseForm : public Form
{
private:

public:
	SubscriptionToCourseForm() : Form(FormType::SubscriptionToCourse) {}
	SubscriptionToCourseForm(SubscriptionToCourseForm&&) = delete;
	SubscriptionToCourseForm(const SubscriptionToCourseForm&) = delete;
	SubscriptionToCourseForm &operator=(const SubscriptionToCourseForm&) = delete;
	~SubscriptionToCourseForm() = default;

	void execute() override;
};

std::ostream &operator<<(std::ostream &o, const SubscriptionToCourseForm &f)
{
	return (o << "SubscriptionToCourseForm(" << static_cast<const Form&>(f) << ")");
}

#endif
