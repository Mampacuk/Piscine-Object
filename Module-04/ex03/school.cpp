#include "school.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "secretary.hpp"
#include "headmaster.hpp"

void School::recruitHeadmaster()
{
	if (!_headmaster)
	{
		_headmaster = std::make_shared<Headmaster>(ft::select_string(ft::constants::names), weak_from_this());
		std::cout << "Recruited a headmaster " << _headmaster->name() << std::endl;
	}
}

void School::recruitSecretary()
{
	if (!_secretary)
	{
		_secretary = std::make_shared<Secretary>(ft::select_string(ft::constants::names));
		std::cout << "Recruited a secretary " << _secretary->name() << std::endl;
	}
}

void School::recruitStudent()
{
	const auto &student = _students.emplace_back(std::make_shared<Student>(ft::select_string(ft::constants::names), weak_from_this()));
	std::cout << "Recruited a student " << student->name() << std::endl;
}

void School::recruitProfessor()
{
	const auto &professor = _professors.emplace_back(std::make_shared<Professor>(ft::select_string(ft::constants::names), weak_from_this()));
	std::cout << "Recruited a professor " << professor->name() << std::endl;
}
