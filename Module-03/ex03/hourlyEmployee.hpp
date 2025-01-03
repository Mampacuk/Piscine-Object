#ifndef HOURLYEMPLOYEE_HPP
# define HOURLYEMPLOYEE_HPP

# include "employee.hpp"

class TempWorker : public WorkingEmployee
{
	public:
		TempWorker() {}
		TempWorker(const int hourly_value) : Employee(hourly_value), WorkingEmployee(hourly_value) {}
		TempWorker(const TempWorker &other) : Employee(other), WorkingEmployee(other) {}
		TempWorker &operator=(const TempWorker &other) { WorkingEmployee::operator=(other); return (*this); }
		~TempWorker() {}
		int executeWorkday()
		{
			return (get_and_reset_hours_to_work() * getHourlyValue());
		}
};

class ContractEmployee : public WorkingEmployee
{
	public:
		ContractEmployee() {}
		ContractEmployee(const int hourly_value) : Employee(hourly_value), WorkingEmployee(hourly_value) {}
		ContractEmployee(const ContractEmployee &other) : Employee(other), WorkingEmployee(other) {}
		ContractEmployee &operator=(const ContractEmployee &other) { WorkingEmployee::operator=(other); return (*this); }
		~ContractEmployee() {}
		int executeWorkday()
		{
			return ((WORKDAY_HOURS - get_and_reset_hours_to_work()) * getHourlyValue());
		}
};

class Apprentice : public WorkingEmployee, public SchooledEmployee
{
	public:
		Apprentice() {}
		Apprentice(const int hourly_value) : Employee(hourly_value), WorkingEmployee(hourly_value) {}
		Apprentice(const Apprentice &other) : Employee(other), WorkingEmployee(other), SchooledEmployee(other) {}
		Apprentice &operator=(const Apprentice &other) { WorkingEmployee::operator=(other); SchooledEmployee::operator=(other); return (*this); }
		~Apprentice() {}
		int executeWorkday()
		{
			const int hourly_value = getHourlyValue();
			const unsigned int hours_worked = get_and_reset_hours_to_work();
			const unsigned int hours_studied = get_and_reset_hours_to_study();
			if (hours_studied + hours_worked > WORKDAY_HOURS)
				throw std::runtime_error("Hours worked and studied exceed maximum amount of working hours");
			return ((WORKDAY_HOURS - hours_worked - hours_studied) * hourly_value + hours_studied * hourly_value / 2);
		}
};

#endif
