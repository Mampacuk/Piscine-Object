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
		void work();
		template <class ToolType>
		ToolType *GetTool()
		{
			for (tool_workshop::iterator it = _tool_workshop.begin(); it != _tool_workshop.end(); ++it)
			{
				ToolType *tool = dynamic_cast<ToolType*>(it->first);
				if (tool)
					return (tool);
			}
			return (NULL);
		}
	// private:
		// bool is_free()
};

std::ostream &operator<<(std::ostream &o, const Worker &w);

# include "Workshop.hpp"

#endif
