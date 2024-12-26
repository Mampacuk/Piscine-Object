#ifndef WORKER_HPP
# define WORKER_HPP

# include "Position.hpp"
# include "Statistic.hpp"
# include "Tool.hpp"

# include <map>

# include "WorkshopBase.hpp"

class Worker
{
	public:
		typedef std::map<Tool*, WorkshopBase*> tool_workshop;
	private:
		Position _coordonnee;
		Statistic _stats;
		tool_workshop _tool_workshop;
	public:
		Worker();
		~Worker();
		Worker(const Position &coordonnee, const Statistic &stat);
		Worker(const Worker &copy);
		Worker &operator=(const Worker &copy);
		int get_x() const;
		int get_y() const;
		int get_z() const;
		int get_level() const;
		int get_exp() const;
		void equip(Tool *tool);
		void unequip(Tool *tool);
		void enroll(WorkshopBase *workshop);
		void leave(WorkshopBase *workshop);
		void work(WorkshopBase *workshop);

		template <class ToolType>
		ToolType *GetTool(bool is_free = false)
		{
			for (tool_workshop::iterator it = _tool_workshop.begin(); it != _tool_workshop.end(); ++it)
			{
				ToolType *tool = dynamic_cast<ToolType*>(it->first);
				if (tool)
				{
					if (is_free)
					{
						if (!it->second)
							return (tool);
					}
					else return (tool);
				}
			}
			return (NULL);
		}

		template <class ToolType>
		void enroll(WorkshopBase *workshop)
		{
			if (!workshop)
				return ;
			if (find_workshop(workshop) != _tool_workshop.end())
				return ;
			Tool *free_tool = GetTool<ToolType>(true);
			if (!free_tool)
				throw std::runtime_error("Can't enroll into a workshop without a free required tool");
			else
			{
				_tool_workshop[free_tool] = workshop;
				workshop->enlist(this);
			}
		}
	private:
		tool_workshop::iterator find_workshop(WorkshopBase *workshop);
};

std::ostream &operator<<(std::ostream &o, const Worker &w);

#endif
