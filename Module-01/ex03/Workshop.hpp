#ifndef WORKSHOP_HPP
# define WORKSHOP_HPP

# include "WorkshopBase.hpp"
# include "Worker.hpp"

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
				throw std::runtime_error("Can't enlist worker without a free required tool");
			_workers.insert(worker);
			worker->enroll(this);
		}
};

#endif
