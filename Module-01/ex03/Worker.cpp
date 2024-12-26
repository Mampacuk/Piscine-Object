#include "Worker.hpp"

Worker::Worker() : _coordonnee(), _stats()
{
	std::cout << *this << " default-constructed" << std::endl;
}

Worker::~Worker()
{
	std::cout << *this << " destroyed" << std::endl;
	for (tool_workshop::iterator it = _tool_workshop.begin(); it != _tool_workshop.end();)
		unequip((it++)->first);
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
	if (!tool || _tool_workshop.find(tool) != _tool_workshop.end())
		return ;
	_tool_workshop.insert(std::make_pair(tool, static_cast<WorkshopBase*>(NULL)));
	tool->set_owner(this);
}

void Worker::unequip(Tool *tool)
{
	if (!tool)
		return ;
	tool_workshop::iterator link = _tool_workshop.find(tool);
	if (link != _tool_workshop.end())
	{
		if (link->second)
			link->second->remove(this);
		_tool_workshop.erase(tool);
		tool->set_owner(NULL);
	}
}

void Worker::leave(WorkshopBase *workshop)
{
	if (!workshop)
		return ;
	tool_workshop::iterator it = find_workshop(workshop);
	if (it == _tool_workshop.end())
		return ;
	it->second = NULL;
	workshop->remove(this);
}

void Worker::work(WorkshopBase *workshop)
{
	tool_workshop::iterator it = find_workshop(workshop);
	if (it == _tool_workshop.end())
		throw std::runtime_error("Worker can't work at a workshop they aren't registered in");
	it->first->use();
}

Worker::tool_workshop::iterator Worker::find_workshop(WorkshopBase *workshop)
{
	tool_workshop::iterator it = _tool_workshop.begin();
	for (; it != _tool_workshop.end(); ++it)
		if (it->second == workshop)
			break ;
	return (it);
}

std::ostream &operator<<(std::ostream &o, const Worker &w)
{
	o << "Worker(coordonnee: Position(x: " << w.get_x() << ", y: "
		<< w.get_y() << ", z: " << w.get_z() << "), stat: Statistic(level: "
		<< w.get_level() << ", exp: " << w.get_exp() << "))";
	return (o);
}
