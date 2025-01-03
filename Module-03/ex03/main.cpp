#include "employeeManagement.hpp"
#include "hourlyEmployee.hpp"
#include <iostream>

#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_MAGENTA "\033[95m"

#define EXPECT_EQ(x, y) \
	if (!(x == y)) \
		std::cerr << RED "FAILURE: " RESET #x RED " != " RESET #y << std::endl; \
	else \
		std::cout << GREEN "SUCCESS: " RESET #x GREEN " == " RESET #y << std::endl;

#define EXPECT_TRUE(x) \
	if (!x) \
		std::cerr << RED "FAILURE: " RESET #x RED " is not TRUE! " RESET << std::endl; \
	else \
		std::cout << GREEN "SUCCESS: " RESET #x GREEN " is TRUE! " RESET << std::endl;

#define EXPECT_THROW(x) try \
{ \
	x; \
	std::cerr << RED "FAILURE: " RESET #x RED " didn't throw!" RESET << std::endl; \
} \
catch (const std::exception &e) \
{ \
	std::cout << GREEN "SUCCESS: caught an exception from " RESET #x GREEN ": " << e.what() << RESET << std::endl; \
}

#define EXPECT_NO_THROW(x) try \
{ \
	x; \
	std::cout << GREEN "SUCCESS: " RESET #x GREEN " didn't throw!" RESET << std::endl; \
} \
catch (const std::exception &e) \
{ \
	std::cerr << RED "FAILURE: caught an exception from " RESET #x RED ": " << e.what() << RESET << std::endl; \
}

#define PRINT_TEST_CASE(suite, test) std::cout << BRIGHT_MAGENTA suite RESET " : " BRIGHT_CYAN test RESET << std::endl;

int main()
{
	EmployeeManager mgr;

	const int thv = 10;
	TempWorker temp(thv);

	const int chv = 20;
	ContractEmployee contract(chv);

	const int ahv = 10;
	Apprentice apprentice(ahv);

	EXPECT_THROW(temp.set_hours_to_work(WORKDAY_HOURS + 1))
	EXPECT_THROW(apprentice.set_hours_to_study(WORKDAY_HOURS + 1))

	temp.set_hours_to_work(5);
	EXPECT_EQ(temp.executeWorkday(), 5 * thv);
	EXPECT_EQ(temp.executeWorkday(), 0);

	contract.set_hours_to_work(5);
	EXPECT_EQ(contract.executeWorkday(), (WORKDAY_HOURS - 5) * chv);
	EXPECT_EQ(contract.executeWorkday(), WORKDAY_HOURS * chv);

	apprentice.set_hours_to_study(WORKDAY_HOURS);
	apprentice.set_hours_to_work(WORKDAY_HOURS);
	EXPECT_THROW(apprentice.executeWorkday());
	
	apprentice.set_hours_to_study(2);
	apprentice.set_hours_to_work(4);
	EXPECT_EQ(apprentice.executeWorkday(), 2 * ahv);

	PRINT_TEST_CASE("EmployeeManager", "Apprentice works for 10 days with 6-1 work-study (expected output: $50)")
	mgr.addEmployee(&apprentice);
	for (int i = 0; i < 10; i++)
	{
		apprentice.set_hours_to_work(6);
		apprentice.set_hours_to_study(1);
		mgr.executeWorkday();
	}
	mgr.calculatePayroll();

	PRINT_TEST_CASE("EmployeeManager", "TempWorker and ContractEmployee join and work for full month\n"
					"(expected output: $300 for apprentice, $600 for temp, $1200 for contract)")
	std::cout << "&TempWorker=" << static_cast<Employee*>(&temp) << ", &Contract=" << static_cast<Employee*>(&contract) << ", &Apprentice=" << static_cast<Employee*>(&apprentice) << std::endl;
	mgr.addEmployee(&temp);
	mgr.addEmployee(&contract);
	for (int i = 0; i < FULL_MONTH_DAYS; i++)
	{
		apprentice.set_hours_to_work(6);
		temp.set_hours_to_work(2);
		contract.set_hours_to_work(5);
		mgr.executeWorkday();
	}
	mgr.calculatePayroll();

	mgr.removeEmployee(&apprentice);
	mgr.removeEmployee(&contract);

	PRINT_TEST_CASE("EmployeeManager", "Remove all except TempWorker, replace 5 days with 1-hour shifts (expected output: $550)")
	for (int i = 0; i < 5; i++)
	{
		temp.set_hours_to_work(1);
		mgr.executeWorkday();
	}
	mgr.calculatePayroll();
}
