#ifndef WORKER_HPP
# define WORKER_HPP

# include "Position.hpp"
# include "Statistic.hpp"
# include "Tool.hpp"

# include <map>

class WorkshopBase;

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
		void work(Tool *tool);
		const WorkshopBase *GetWorkshop(const Tool *tool) const;

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
		void enroll(Workshop<ToolType> *workshop)
		{
			if (!workshop)
				return ;
			if (find_workshop() != _tool_workshop.end())
				return ;
			Tool *tool = GetTool<ToolType>(true);
			if (!tool)
				return ;
			else
			{
				_tool_workshop[tool] = workshop;
				workshop->enlist(this);
			}
		}
	private:
		tool_workshop::iterator find_tool(Tool *tool);
		tool_workshop::const_iterator find_tool(Tool *tool) const;
		tool_workshop::iterator find_workshop(WorkshopBase *workshop);
		tool_workshop::const_iterator find_workshop(WorkshopBase *workshop) const;
};

std::ostream &operator<<(std::ostream &o, const Worker &w);

# include "Workshop.hpp"

#endif
