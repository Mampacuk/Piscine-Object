#include "secretary.hpp"
#include "forms.hpp"
#include "rooms.hpp"
#include "school.hpp"

// Simple Factory from Factory Method pattern
std::shared_ptr<Form> Secretary::createForm(FormType p_formType)
{
	if (!in_room<SecretarialOffice>())
		throw std::runtime_error("Secretary " + name() + " is not in their office to work");
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

void Secretary::on_event(Event event)
{
	auto current_room = room().lock();
	switch (event)
	{
	case Event::RingBell:
		if (std::dynamic_pointer_cast<SecretarialOffice>(current_room))
		{
			current_room->exit(weak_from_this());
			ft::weak_lock(ft::weak_lock(_school)->find_room<StaffRestRoom>())->enter(weak_from_this());
		}
		else if (std::dynamic_pointer_cast<StaffRestRoom>(current_room))
		{
			current_room->exit(weak_from_this());
			ft::weak_lock(ft::weak_lock(_school)->find_room<SecretarialOffice>())->enter(weak_from_this());
		}
		else
			throw std::runtime_error("Secretary " + name() + " is not in a correct room to react to the bell");
	}
}

std::ostream &operator<<(std::ostream &o, const Secretary &s)
{
	return (o << "Secretary(" << static_cast<const Staff&>(s) << ")");
}
