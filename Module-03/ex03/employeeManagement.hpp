#ifndef EMPLOYEEMANAGEMENT_HPP
# define EMPLOYEEMANAGEMENT_HPP

# include "employee.hpp"

# include <deque>
# include <map>
# include <iostream>

# define FULL_MONTH_DAYS 30

class EmployeeManager
{
	public:
		EmployeeManager() : _records() {}
		EmployeeManager(const EmployeeManager &other) { _records = other._records; }
		EmployeeManager &operator=(const EmployeeManager &other) { _records = other._records; return (*this); }
		~EmployeeManager() {}

		void addEmployee(Employee *employee)
		{
			if (employee && _records.find(employee) == _records.end())
				_records.insert(std::make_pair(employee, std::deque<int>()));
		}

		void removeEmployee(Employee *employee)
		{
			_records.erase(employee);
		}

		void executeWorkday()
		{
			for (records::iterator record = _records.begin(); record != _records.end(); record++)
			{
				Employee &e = *record->first;
				wages &w = record->second;

				if (w.size() == FULL_MONTH_DAYS)
					w.pop_front();
				w.push_back(e.executeWorkday());
			}
		}

		void calculatePayroll() const
		{
			for (records::const_iterator record = _records.begin(); record != _records.end(); record++)
			{
				int payroll = 0;
				Employee &e = *record->first;
				const wages &w = record->second;
				for (wages::const_iterator wage = w.begin(); wage != w.end(); wage++)
					payroll += *wage;
				std::cout << "Employee " << &e << " has earned $" << payroll << " past month" << std::endl;
			}
		}
	private:
		typedef std::deque<int> wages;
		typedef std::map<Employee*, wages> records;
		records _records;
};

#endif
