#ifndef WORKSHOP_HPP
# define WORKSHOP_HPP

# include "Worker.hpp"

# include <set>

class WorkshopBase
{
	private:
		// deleted {
		WorkshopBase(const WorkshopBase&) {}
		WorkshopBase &operator=(const WorkshopBase&) {}
		// } deleted
	protected:
		typedef std::set<Worker*> workers;
		workers _workers;
	public:
		WorkshopBase() : _workers() {}
		virtual ~WorkshopBase()
		{
			for (workers::iterator it = _workers.begin(); it != _workers.end(); ++it)
				(*it)->leave(this);
		}

		void remove(Worker *worker)
		{
			if (!worker)
				return ;
			size_t erased = _workers.erase(worker);
			if (erased)
				worker->leave(this);
		}
};

template <class ToolType>
class Workshop : public WorkshopBase
{
	public:
		Workshop() : WorkshopBase() {}
		~Workshop() {}
		Workshop(const Workshop &copy) : WorkshopBase(copy) {}
		Workshop &operator=(const Workshop &rhs)
		{
			WorkshopBase::operator=(rhs);
			return (*this);
		}

		void enlist(Worker *worker)
		{
			if (!worker || _workers.find(worker) != _workers.end())
				return ;
			Tool *free_tool = worker->GetTool<ToolType>(true);
			if (!free_tool)
				throw std::runtime_error("Can't enlist worker without required tool");
			_workers.insert(worker);
			worker->enroll(this);
		}
};

#endif
