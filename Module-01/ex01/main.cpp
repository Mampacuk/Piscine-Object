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

int main()
{
	Worker worker1;
	Worker worker2;
	Shovel shovel;

	EXPECT_THROW(worker1.use_tool())

	EXPECT_EQ(shovel.numberOfUses, 0)
	EXPECT_EQ(shovel.owner, NULL)
	
	worker1.set_tool(&shovel);
	EXPECT_EQ(shovel.owner, &worker1)
	worker1.use_tool();
	EXPECT_EQ(shovel.numberOfUses, 1)

	worker2.set_tool(&shovel);
	EXPECT_EQ(shovel.owner, &worker2)
	EXPECT_THROW(worker1.use_tool())

	worker2.unset_tool();
	EXPECT_EQ(shovel.owner, NULL)

	{
		Worker worker3;

		worker3.set_tool(&shovel);
		EXPECT_EQ(shovel.owner, &worker3)
	}
	EXPECT_EQ(shovel.owner, NULL)

	{
		Shovel shov;

		worker1.set_tool(&shov);
		EXPECT_EQ(worker1.get_tool(), &shov)
	}
	EXPECT_EQ(worker1.get_tool(), NULL)
}
