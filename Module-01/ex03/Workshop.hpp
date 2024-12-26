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
			worker->enroll<ToolType>(this);
			_workers.insert(worker);
		}
};

#endif
