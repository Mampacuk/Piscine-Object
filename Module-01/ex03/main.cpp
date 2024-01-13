#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"

#define EXPECT_EQ(x, y) \
	if (!(x == y)) \
		std::cerr << RED "FAILURE: " RESET #x RED " != " RESET #y << std::endl; \
	else \
		std::cout << GREEN "SUCCESS: " RESET #x GREEN " == " RESET #y << std::endl;

#define EXPECT_THROW(x) try \
{ \
	x; \
	std::cerr << RED "FAILURE: " RESET #x RED " didn't throw!" RESET << std::endl; \
} \
catch (const std::exception &e) \
{ \
	std::cout << GREEN "SUCCESS: caught an exception from " RESET #x GREEN ": " << e.what() << RESET << std::endl; \
}

#include "Worker.hpp"
#include "Shovel.hpp"
#include "Hammer.hpp"

int main()
{
	// create 3-way link; destroy the members
	Worker worker1;
	Worker worker2;
	Shovel shovel;
	Hammer hammer;

	EXPECT_THROW(shovel.use())
	EXPECT_EQ(shovel.get_number_of_uses(), 0)
	EXPECT_EQ(shovel.get_owner(), NULL)
	
	EXPECT_EQ(worker1.GetTool<Shovel>(), NULL)

	worker1.equip(&shovel);
	EXPECT_EQ(worker1.GetTool<Shovel>(), &shovel)
	EXPECT_EQ(shovel.get_owner(), &worker1)
	shovel.use();
	EXPECT_EQ(shovel.get_number_of_uses(), 1)

	worker1.equip(&hammer);
	hammer.use();
	EXPECT_EQ(worker1.GetTool<Hammer>(), &hammer)

	worker2.equip(&shovel);
	EXPECT_EQ(worker1.GetTool<Shovel>(), NULL)
	
	worker2.unequip(&shovel);
	EXPECT_EQ(worker2.GetTool<Shovel>(), NULL)
	worker1.unequip(&hammer);
	EXPECT_EQ(worker1.GetTool<Hammer>(), NULL)
	{
		Worker worker3;

		worker3.equip(&shovel);
		EXPECT_EQ(shovel.get_owner(), &worker3)
	}
	EXPECT_EQ(shovel.get_owner(), NULL)

	{
		Shovel shov;

		worker1.unequip(&shov);
		EXPECT_EQ(worker1.GetTool<Shovel>(), &shov)
	}
	EXPECT_EQ(worker1.GetTool<Shovel>(), NULL)
}
