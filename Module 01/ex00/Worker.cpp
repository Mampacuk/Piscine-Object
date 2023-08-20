#include "Worker.hpp"

Worker::Worker() : coordonnee(), stat()
{
	std::cout << *this << " default-constructed" << std::endl;
}

Worker::~Worker()
{
	std::cout << *this << " destroyed" << std::endl;
}

Worker::Worker(const Position &coordonnee, const Statistic &stat) : coordonnee(coordonnee), stat(stat)
{
	std::cout << *this << " arg-constructed" << std::endl;
}

Worker::Worker(const Worker &copy) : coordonnee(copy.coordonnee), stat(copy.stat)
{
	std::cout << "Worker copy-constructed from " << copy << std::endl;
}

Worker &Worker::operator=(const Worker &rhs)
{
	std::cout << *this << " assigned to " << rhs << std::endl;
	coordonnee = rhs.coordonnee;
	stat = rhs.stat;
	return (*this);
}

std::ostream &operator<<(std::ostream &o, const Worker &w)
{
	o << "Worker(coordonnee: Position(x: " << w.get_x() << ", y: "
		<< w.get_y() << ", z: " << w.get_z() << "), stat: Statistic(level: "
		<< w.get_level() << ", exp: " << w.get_exp() << "))";
	return (o);
}
