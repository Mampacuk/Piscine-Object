#include "school.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "secretary.hpp"
#include "headmaster.hpp"
#include "rooms.hpp"
#include "bell.hpp"
#include "course.hpp"
#include "forms.hpp"

School::School() : _secretary(), _headmaster(), _students(), _professors(), _rooms()
{
	build_room<SecretarialOffice>();
	build_room<HeadmasterOffice>();
	build_room<StaffRestRoom>();
	build_room<Courtyard>();
}

void School::recruitHeadmaster()
{
	if (!_headmaster)
	{
		_headmaster = std::make_shared<Headmaster>(ft::select_string(ft::constants::names), weak_from_this());
		std::cout << "Recruited a headmaster " << _headmaster->name() << std::endl;
		subscribe_to_bell(_headmaster);
		ft::weak_lock(find_room<HeadmasterOffice>())->enter(_headmaster);
	}
}

void School::recruitSecretary()
{
	if (!_secretary)
	{
		_secretary = std::make_shared<Secretary>(ft::select_string(ft::constants::names), weak_from_this());
		std::cout << "Recruited a secretary " << _secretary->name() << std::endl;
		subscribe_to_bell(_secretary);
		ft::weak_lock(find_room<SecretarialOffice>())->enter(_secretary);
	}
}

void School::recruitStudent()
{
	const auto &student = _students.emplace_back(std::make_shared<Student>(ft::select_string(ft::constants::names), weak_from_this()));
	subscribe_to_bell(student);
	std::cout << "Recruited a student " << student->name() << std::endl;
}

void School::recruitProfessor()
{
	const auto &professor = _professors.emplace_back(std::make_shared<Professor>(ft::select_string(ft::constants::names), weak_from_this()));
	subscribe_to_bell(professor);
	std::cout << "Recruited a professor " << professor->name() << std::endl;
}

void School::subscribe_to_bell(std::weak_ptr<Observer> observer)
{
	if (!_headmaster)
		recruitHeadmaster();
	_headmaster->get_bell().subscribe(std::move(observer));
}

void School::requestRingBell()
{
	if (!_headmaster)
		recruitHeadmaster();
	_headmaster->ring_bell();
}

void School::launchClasses()
{
	if (!_headmaster)
		recruitHeadmaster();
	_headmaster->make_professors_do_class();
}

std::weak_ptr<Course> School::getCourse(std::string p_name) const
{
	if (auto prof_it = std::find_if(_professors.begin(), _professors.end(),
									[&p_name](const professor &p)
									{
										auto course = p->current_course().lock();
										return (course && course->name() == p_name); });
		prof_it != _professors.end())
		return ((*prof_it)->current_course());
	return (std::weak_ptr<Course>());
}

void School::graduationCeremony() const
{
	for (const auto &prof : _professors)
	{
		if (auto course = prof->current_course().lock())
		{
			for (const auto &[student, classes_attended] : course->get_attendance())
			{
				if (classes_attended >= course->classes_to_graduate())
				{
					auto graduation_form = std::static_pointer_cast<CourseFinishedForm>(ft::weak_lock(_headmaster->request_form(FormType::CourseFinished)));
					graduation_form->set_alumnus(student);
					graduation_form->set_course(course);
				}
			}
		}
	}
	_headmaster->sign_and_execute_all_forms();
}

void School::runDayRoutine()
{
	// 1. launch classes
	launchClasses();
	// 2. allow student and professor to go on recreation
	requestRingBell();
	// 3. launch classes
	requestRingBell();
	launchClasses();
	// 4. launch lunch
	requestRingBell();
	// 5. launch classes
	requestRingBell();
	launchClasses();
	// 6. allow student and professor to go on recreation
	requestRingBell();
	// 7. launch classes
	requestRingBell();
	launchClasses();
}
