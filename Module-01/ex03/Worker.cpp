#include "Worker.hpp"

Worker::Worker() : _coordonnee(), _stats()
{
	std::cout << *this << " default-constructed" << std::endl;
}

Worker::~Worker()
{
	std::cout << *this << " destroyed" << std::endl;
}

Worker::Worker(const Position &coordonnee, const Statistic &stat) : _coordonnee(coordonnee), _stats(stat)
{
	std::cout << *this << " arg-constructed" << std::endl;
}

Worker::Worker(const Worker &copy) : _coordonnee(copy._coordonnee), _stats(copy._stats)
{
	std::cout << "Worker copy-constructed from " << copy << std::endl;
}

Worker &Worker::operator=(const Worker &rhs)
{
	std::cout << *this << " assigned to " << rhs << std::endl;
	_coordonnee = rhs._coordonnee;
	_stats = rhs._stats;
	return (*this);
}

int Worker::get_x() const
{
	return (_coordonnee.x);
}

int Worker::get_y() const
{
	return (_coordonnee.y);
}

int Worker::get_z() const
{
	return (_coordonnee.z);
}

int Worker::get_level() const
{
	return (_stats.level);
}

int Worker::get_exp() const
{
	return (_stats.exp);
}

void Worker::equip(Tool *tool)
{
	if (!tool)
		return ;
	tool->set_owner(this);
	_tool_workshop.insert(std::make_pair(tool, static_cast<WorkshopBase*>(NULL)));
}

void Worker::unequip(Tool *tool)
{
	size_t erased = _tool_workshop.erase(tool);
	if (erased)
		tool->set_owner(NULL);
}

void Worker::enroll_workshop(WorkshopBase *workshop)
{
	if (!workshop || _workshops.find(workshop) != _workshops.end())
		return ;
	_workshops.insert(workshop);
	try
	{
		workshop->add_worker(this);
	}
	catch(const std::runtime_error&)
	{
		_workshops.erase(workshop);
	}
}

void Worker::leave_workshop(WorkshopBase *workshop)
{
	if (!workshop)
		return ;
	size_t erased = _workshops.erase(workshop);
	if (erased)
	{
		workshop->remove_worker(this);
	}
}

std::ostream &operator<<(std::ostream &o, const Worker &w)
{
	o << "Worker(coordonnee: Position(x: " << w.get_x() << ", y: "
		<< w.get_y() << ", z: " << w.get_z() << "), stat: Statistic(level: "
		<< w.get_level() << ", exp: " << w.get_exp() << "))";
	return (o);
}
