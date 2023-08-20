#ifndef WORKER_HPP
# define WORKER_HPP

# include "Position.hpp"
# include "Statistic.hpp"
# include "Tool.hpp"

# include <set>

class Worker
{
	public:
		typedef std::set<Tool*> tools;
	private:
		Position _coordonnee;
		Statistic _stats;
		tools _tools;
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
		void add_tool(Tool *tool);
		void remove_tool(Tool *tool);
		template <class ToolType>
		ToolType *GetTool()
		{
			for (tools::iterator it = _tools.begin(); it != _tools.end(); ++it)
			{
				ToolType *tool = dynamic_cast<ToolType*>(*it);
				if (tool)
					return (tool);
			}
			return (NULL);
		}
};

std::ostream &operator<<(std::ostream &o, const Worker &w);

#endif
