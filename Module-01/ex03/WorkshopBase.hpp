#ifndef WORKSHOPBASE_HPP
# define WORKSHOPBASE_HPP

# include <set>

class Worker;

class WorkshopBase
{
	private:
		// deleted {
		WorkshopBase(const WorkshopBase&);
		WorkshopBase &operator=(const WorkshopBase&);
		// } deleted
	protected:
		typedef std::set<Worker*> workers;
		workers _workers;
	public:
		WorkshopBase();
		virtual ~WorkshopBase();
		void remove(Worker *worker);
		void executeWorkDay();
		virtual void enlist(Worker *worker) = 0;
		const workers &get_workers() const;
};

#endif
