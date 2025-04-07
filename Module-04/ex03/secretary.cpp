#include "secretary.hpp"
#include "forms.hpp"

// Simple Factory from Factory Method pattern
std::shared_ptr<Form> Secretary::createForm(FormType p_formType)
{
	std::shared_ptr<Form> form;
	switch (p_formType)
	{
		case FormType::CourseFinished:
			form = std::make_shared<CourseFinishedForm>();
			break ;
		case FormType::NeedCourseCreation:
			form = std::make_shared<NeedCourseCreationForm>();
			break ;
		case FormType::NeedMoreClassRoom:
			form = std::make_shared<NeedMoreClassRoomForm>();
			break ;
		case FormType::SubscriptionToCourse:
			form = std::make_shared<SubscriptionToCourseForm>();
			break ;
		default:
			throw std::invalid_argument("Unexpected FormType enum value");
	}
	std::cout << "Secretary " << name() << " has created a " << *form << " form" << std::endl;
	return (form);
}

std::ostream &operator<<(std::ostream &o, const Secretary &s)
{
	return (o << "Secretary(" << static_cast<const Staff&>(s) << ")");
}
