#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

#include <iostream>
#include <vector>

// the following method satisfies the Liskov substitution principle, as it is ensured that
// any object of subtype of Shape can work correctly in this function, i.e. its area and perimeter
// are printed. the function does this without knowing or caring about the specific type of the object.
// classes derived from Shape are able to replace the Shape class in any context without introducing
// errors or unexpected behavior, as all of them get their area and perimeter printed.
void	print_shape_areas_and_perimeters(const std::vector<Shape*> &shapes)
{
	for (std::vector<Shape*>::const_iterator shape = shapes.begin(); shape != shapes.end(); shape++)
		std::cout << "Shape area=" << (*shape)->area() << ", perimeter=" << (*shape)->perimeter() << std::endl;
}

int main()
{
	Shape *triangle = new Triangle(1, 1, std::sqrt(2));  // half a unit square
	Shape *rectangle = new Rectangle(1, 1);  // unit square
	Shape *circle = new Circle(1);  // unit circle

	std::vector<Shape*> shapes;
	shapes.push_back(triangle);
	shapes.push_back(rectangle);
	shapes.push_back(circle);

	print_shape_areas_and_perimeters(shapes);
}
