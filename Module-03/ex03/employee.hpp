#ifndef EMPLOYEE_HPP
# define EMPLOYEE_HPP

# define WORKDAY_HOURS 7

# include <stdexcept>

// Interface Segregation Principle (ISP) states that "clients should not be forced to depend
// upon interfaces that they do not use." all required subtypes of employees need their hours 
// worked set, so WorkingEmployee with a public set_hours_to_work() was designed. a violation
// of ISP would've been adding set_hours_to_work() to Employee interface itself---that would
// bloat and pollute the interface, making it "fat" and forcing Employee derivatives that don't
// need their hours worked set to implement the method. similarly, for Apprentice, a separate
// SchooledEmployee interface was defined, and the set_hours_to_study() was taken out here
// instead of adding it to WorkingEmployee or Employee interfaces---that would clearly be a
// violation of ISP.
class Employee
{
	public:
		Employee() : hourlyValue(0) {}
		Employee(const int hourlyValue) : hourlyValue(hourlyValue) {}
		Employee(const Employee &other) : hourlyValue(other.hourlyValue) {}
		Employee &operator=(const Employee &other) { hourlyValue = other.hourlyValue; return (*this); }
		virtual ~Employee() {}
	private:
		int hourlyValue;
	protected:
		int getHourlyValue() const { return (hourlyValue); }
	public:
		virtual int executeWorkday() = 0;
};


class WorkingEmployee : virtual public Employee
{
	private:
		unsigned int _hours_to_work;
	public:
		WorkingEmployee() : _hours_to_work(0) {}
		WorkingEmployee(const int hourly_value) : Employee(hourly_value), _hours_to_work(0) {}
		WorkingEmployee(const WorkingEmployee &other) : Employee(other), _hours_to_work(other._hours_to_work) {}
		WorkingEmployee &operator=(const WorkingEmployee &other) { Employee::operator=(other); _hours_to_work = other._hours_to_work; return (*this); }
		virtual ~WorkingEmployee() {}
		void set_hours_to_work(const unsigned int hours_to_work)
		{
			if (hours_to_work > WORKDAY_HOURS)
				throw std::invalid_argument("Maximum amount of working hours a day exceeded");
			_hours_to_work = hours_to_work;
		}
	protected:
		unsigned int get_and_reset_hours_to_work()
		{
			const unsigned int hours_to_work = _hours_to_work;
			_hours_to_work = 0;
			return (hours_to_work);
		}
};

class SchooledEmployee : virtual public Employee
{
	private:
		unsigned int _hours_to_study;
	public:
		SchooledEmployee() : _hours_to_study(0) {}
		SchooledEmployee(const int hourly_value) : Employee(hourly_value), _hours_to_study(0) {}
		SchooledEmployee(const SchooledEmployee &other) : Employee(other), _hours_to_study(other._hours_to_study) {}
		SchooledEmployee &operator=(const SchooledEmployee &other) { Employee::operator=(other); _hours_to_study = other._hours_to_study; return (*this); }
		virtual ~SchooledEmployee() {}
		void set_hours_to_study(const unsigned int hours_to_study)
		{
			if (hours_to_study > WORKDAY_HOURS)
				throw std::invalid_argument("Maximum amount of studying hours a day exceeded");
			_hours_to_study = hours_to_study;
		}
	protected:
		unsigned int get_and_reset_hours_to_study()
		{
			const unsigned int hours_to_study = _hours_to_study;
			_hours_to_study = 0;
			return (hours_to_study);
		}
};

#endif
