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

#define PRINT_TEST_CASE(suite, test) std::cout << BRIGHT_MAGENTA suite " : " BRIGHT_CYAN test RESET << std::endl;

#include "Worker.hpp"
#include "Shovel.hpp"
#include "Hammer.hpp"
#include "Workshop.hpp"

int main()
{
	Worker worker1(Position(1, 1, 1), Statistic(1, 1));
	Worker worker2(Position(2, 2, 2), Statistic(2, 2));
	Shovel shovel;
	Hammer hammer;

	PRINT_TEST_CASE("TOOL", "initialization")
	EXPECT_THROW(shovel.use())
	EXPECT_EQ(shovel.get_number_of_uses(), 0)
	EXPECT_EQ(shovel.get_owner(), NULL)
	
	PRINT_TEST_CASE("WORKER", "initialization")
	EXPECT_EQ(worker1.GetTool<Shovel>(), NULL)

	PRINT_TEST_CASE("WORKER", "single tool equipped")
	PRINT_TEST_CASE("TOOL", "owner assigned")
	worker1.equip(&shovel);
	EXPECT_EQ(worker1.GetTool<Shovel>(), &shovel)
	EXPECT_EQ(shovel.get_owner(), &worker1)

	PRINT_TEST_CASE("TOOL", "usage incremented")
	shovel.use();
	EXPECT_EQ(shovel.get_number_of_uses(), 1)

	PRINT_TEST_CASE("WORKER", "multiple tools equipped")
	worker1.equip(&hammer);
	hammer.use();
	EXPECT_EQ(worker1.GetTool<Hammer>(), &hammer)

	PRINT_TEST_CASE("WORKER", "when equipping an already equipped tool, unequips the tool from its current owner")
	worker2.equip(&shovel);
	EXPECT_EQ(worker1.GetTool<Shovel>(), NULL)
	
	PRINT_TEST_CASE("WORKER", "unequipping")
	worker2.unequip(&shovel);
	EXPECT_EQ(worker2.GetTool<Shovel>(), NULL)
	worker1.unequip(&hammer);
	EXPECT_EQ(worker1.GetTool<Hammer>(), NULL)

	PRINT_TEST_CASE("WORKER", "unequips tool upon destruction")
	{
		Worker worker3;

		worker3.equip(&shovel);
		EXPECT_EQ(shovel.get_owner(), &worker3)
	}
	EXPECT_EQ(shovel.get_owner(), NULL)

	PRINT_TEST_CASE("TOOL", "discards owner upon destruction")
	{
		Shovel shov;

		worker1.equip(&shov);
		EXPECT_EQ(worker1.GetTool<Shovel>(), &shov)
	}
	EXPECT_EQ(worker1.GetTool<Shovel>(), NULL)

	Workshop<Shovel> shovelWorkshop1;

	PRINT_TEST_CASE("WORKSHOP", "can't enlist a worker without any tools")
	PRINT_TEST_CASE("WORKER", "can't enroll into a workshop without any tools")
	EXPECT_THROW(shovelWorkshop1.enlist(&worker1))
	EXPECT_THROW(worker1.enroll<Shovel>(&shovelWorkshop1))
	EXPECT_TRUE(shovelWorkshop1.get_workers().empty())

	PRINT_TEST_CASE("WORKSHOP", "can't enlist a worker with the wrong tool")
	PRINT_TEST_CASE("WORKER", "can't enroll into a workshop with the wrong tool")
	worker1.equip(&hammer);
	EXPECT_THROW(shovelWorkshop1.enlist(&worker1))
	EXPECT_THROW(worker1.enroll<Shovel>(&shovelWorkshop1))
	EXPECT_TRUE(shovelWorkshop1.get_workers().empty())

	PRINT_TEST_CASE("WORKSHOP", "enlist a worker successfully")
	Workshop<Shovel> shovelWorkshop2;
	worker1.equip(&shovel);
	int old_shovel_no_of_uses = shovel.get_number_of_uses();
	EXPECT_NO_THROW(shovelWorkshop2.enlist(&worker1))
	EXPECT_NO_THROW(worker1.work(&shovelWorkshop2))
	EXPECT_EQ(shovel.get_number_of_uses(), old_shovel_no_of_uses + 1)
	EXPECT_EQ(shovelWorkshop2.get_workers().size(), 1)
	
	PRINT_TEST_CASE("WORKSHOP", "remove a worker successfully")
	shovelWorkshop2.remove(&worker1);
	EXPECT_THROW(worker1.work(&shovelWorkshop2))
	EXPECT_TRUE(shovelWorkshop2.get_workers().empty())

	PRINT_TEST_CASE("WORKER", "enroll into a workshop successfully")
	worker1.enroll<Shovel>(&shovelWorkshop2);

	PRINT_TEST_CASE("WORKSHOP", "can't enlist a worker with no free tools")
	EXPECT_THROW(shovelWorkshop1.enlist(&worker1))
	PRINT_TEST_CASE("WORKER", "can't enroll into a workshop with no free tools")
	EXPECT_THROW(worker1.enroll<Shovel>(&shovelWorkshop1))

	PRINT_TEST_CASE("WORKER", "enroll into multiple workshops")
	Workshop<Hammer> hammerWorkshop;
	worker1.enroll<Hammer>(&hammerWorkshop);
	EXPECT_NO_THROW(worker1.work(&hammerWorkshop))
	EXPECT_NO_THROW(worker1.work(&shovelWorkshop2))

	PRINT_TEST_CASE("WORKER", "leave a workshop successfuly")
	worker1.leave(&shovelWorkshop2);
	worker1.leave(&hammerWorkshop);
	EXPECT_TRUE(shovelWorkshop2.get_workers().empty() && hammerWorkshop.get_workers().empty())

	PRINT_TEST_CASE("WORKSHOP", "executeWorkDay()")
	Shovel extra_shovel;
	worker2.equip(&extra_shovel);
	worker2.enroll<Shovel>(&shovelWorkshop2);
	worker1.enroll<Shovel>(&shovelWorkshop2);
	shovelWorkshop2.executeWorkDay();

	// 3-way link: worker -> tool -> workshop
	PRINT_TEST_CASE("Worker-Tool-Workshop", "destroy worker")
	{
		Worker worker3;

		worker3.equip(&shovel);
		shovelWorkshop1.enlist(&worker3);
	}
	EXPECT_TRUE(shovelWorkshop1.get_workers().empty())

	PRINT_TEST_CASE("Worker-Tool-Workshop", "destroy tool")
	{
		Hammer extra_hammer;
		worker2.equip(&extra_hammer);
		worker2.enroll<Hammer>(&hammerWorkshop);
	}
	EXPECT_TRUE(hammerWorkshop.get_workers().empty())

	PRINT_TEST_CASE("Worker-Tool-Workshop", "destroy workshop")
	{
		Workshop<Hammer> workshop;
		workshop.enlist(&worker1);
		// the hammer is occupied now
		EXPECT_EQ(worker1.GetTool<Hammer>(false), &hammer);
	}
	// still has the hammer, and it is free now
	EXPECT_EQ(worker1.GetTool<Hammer>(true), &hammer);
}
