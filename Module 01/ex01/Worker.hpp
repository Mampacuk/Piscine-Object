#ifndef WORKER_HPP
# define WORKER_HPP

# include "Position.hpp"
# include "Shovel.hpp"
# include "Statistic.hpp"

// AGGREGATION:
//
class Worker
{
	private:
		Position coordonnee;
		Statistic stat;
		Shovel *shovel;
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
		void set_tool(Shovel *shovel);
		void unset_tool();
		void use_tool();
};

std::ostream &operator<<(std::ostream &o, const Worker &w);

#endif
