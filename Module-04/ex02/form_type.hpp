#ifndef FORM_TYPE_HPP
# define FORM_TYPE_HPP

enum class FormType
{
	CourseFinished,		  // graduation form to graduate a student when they attended
						  // enough classes

	NeedMoreClassRoom,    // when a professor, when trying to start a class, can't find
						  // a free classroom, a new classroom needs to be created to hold
						  // the class

	NeedCourseCreation,   // when a professor has no courses to teach,
						  // create a course and assign it to them

	SubscriptionToCourse  // when a student has no courses, look for a course and
						  // subscribe the student to it
};

#endif
