#include "WorkshopBase.hpp"
#include "Worker.hpp"

WorkshopBase::WorkshopBase() : _workers() {}

WorkshopBase::~WorkshopBase()
{
	for (workers::iterator it = _workers.begin(); it != _workers.end();)
		remove(*(it++));
}

void WorkshopBase::remove(Worker *worker)
{
	if (!worker)
		return ;
	const size_t erased = _workers.erase(worker);
	if (erased)
		worker->leave(this);
}

void WorkshopBase::executeWorkDay()
{
	for (workers::iterator it = _workers.begin(); it != _workers.end(); ++it)
		(*it)->work(this);
}

const WorkshopBase::workers &WorkshopBase::get_workers() const
{
	return _workers;
}
