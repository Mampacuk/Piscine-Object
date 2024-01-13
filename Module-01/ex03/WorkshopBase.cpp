#include "WorkshopBase.hpp"
#include "Worker.hpp"

WorkshopBase::WorkshopBase() : _workers() {}

WorkshopBase::~WorkshopBase()
{
	for (workers::iterator it = _workers.begin(); it != _workers.end(); ++it)
		(*it)->leave(this);
}

void WorkshopBase::remove(Worker *worker)
{
	if (!worker)
		return ;
	size_t erased = _workers.erase(worker);
	if (erased)
		worker->leave(this);
}

void WorkshopBase::executeWorkDay()
{
	for (workers::iterator it = _workers.begin(); it != _workers.end(); ++it)
		(*it)->work(this);
}
