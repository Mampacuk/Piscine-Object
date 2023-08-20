#ifndef WORKSHOP_HPP
# define WORKSHOP_HPP

# include "Worker.hpp"

# include <set>

class WorkshopBase
{
	protected:
		typedef std::set<Worker*> workers;
		workers _workers;
	public:
		WorkshopBase() : _workers() {}
		virtual ~WorkshopBase()
		{
			
		}
		WorkshopBase(const WorkshopBase &copy) : _workers(copy._workers) {}
		WorkshopBase &operator=(const WorkshopBase &rhs)
		{
			_workers = rhs._workers;
			return (*this);
		}

		virtual void add_worker(Worker *worker) = 0;

		void remove_worker(Worker *worker)
		{
			if (!worker)
				return ;
			size_t erased = _workers.erase(worker);
			if (erased)
			{
				worker->leave_workshop(this);
			}
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

		void add_worker(Worker *worker)
		{
			if (!worker)
				return ;
			if (!worker->GetTool<ToolType>())
				throw std::runtime_error("Can't add worker without required tool");
			if (_workers.find(worker) != _workers.end())
				return ;
			_workers.insert(worker);
			worker->enroll_workshop(this);
		}
};

#endif
