#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"

#define EXPECT_EQ(x, y) \
	if (!(x == y)) \
		std::cerr << RED "FAILURE: " RESET #x RED " != " RESET #y << std::endl; \
	else \
		std::cout << GREEN "SUCCESS: " RESET #x GREEN " == " RESET #y << std::endl;

#define EXPECT_FLOAT_EQ(x, y) \
	if (!(std::fabs(x - y) < std::numeric_limits<float>::epsilon())) \
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

#include "Graph.hpp"

int main()
{
	EXPECT_THROW(Line(Vector2(), Vector2()))

	Line vertical(Vector2(0.f, 1.f), Vector2(0.f, 2.f));
	Line horizontal(Vector2(0.f, 2.f), Vector2(2.f, 2.f));
	Line xy(Vector2(0.f, 0.f), Vector2(1.f, 1.f));
	Line offsetted(Vector2(0.f, 1.f), Vector2(1.f, 2.f));
	
	EXPECT_FLOAT_EQ(vertical.get_y_factor(), 0.f)
	EXPECT_FLOAT_EQ(horizontal.get_x_factor(), 0.f)
	EXPECT_FLOAT_EQ(offsetted.get_offset(), 1.f)

	EXPECT_FLOAT_EQ(vertical.solve_for_x(15.f).get_x(), 0.f)
	EXPECT_FLOAT_EQ(horizontal.solve_for_y(15.f).get_y(), 2.f)
	EXPECT_FLOAT_EQ(xy.solve_for_x(1.f).get_y(), 1.f)
	EXPECT_FLOAT_EQ(xy.solve_for_y(1000.f).get_x(), 1000.f)

	EXPECT_THROW(vertical.solve_for_y(0.f))
	EXPECT_THROW(vertical.solve_for_y(1.f))
	EXPECT_THROW(horizontal.solve_for_x(2.f))
	EXPECT_THROW(horizontal.solve_for_x(1.f))

	Graph graph;

	EXPECT_THROW(graph.read_file("blabla"))
	EXPECT_THROW(graph.read_file("files/incomplete.txt"))
	EXPECT_THROW(graph.read_file("files/invalid1.txt"))
	EXPECT_THROW(graph.read_file("files/invalid2.txt"))

	EXPECT_THROW(graph.show(1, 1, 2, 3))
	EXPECT_THROW(graph.show(5, 1, 2, 3))
	EXPECT_THROW(graph.show(1, 2, 4, 3))

	graph.add_line(xy);
	graph.show(-2, 2, -2, 2);
	std::cout << std::endl;

	graph.add_line(horizontal);
	graph.show(-4, 4, -4, 4);
	std::cout << std::endl;

	graph.add_line(vertical);
	graph.show(-2, 3, -3, 5);
	std::cout << std::endl;

	graph.add_point(Vector2(4.2f, 5.8f));
	graph.add_point(Vector2(3.4999f, -2.5f));
	graph.show(0, 5, -4, 7);
	std::cout << std::endl;

	graph.read_file("file/valid.txt");
	graph.show(-3, 5, 4, 7);
}
