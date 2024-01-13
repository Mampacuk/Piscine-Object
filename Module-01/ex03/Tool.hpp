#ifndef TOOL_HPP
# define TOOL_HPP

# include <iostream>

class Worker;

class Tool
{
	private:
		int _number_of_uses;
		Worker *_owner;
		// delete {
		Tool(const Tool &copy);
		Tool &operator=(const Tool &copy);
		// } delete
	protected:
		void increment_usage();
	public:
		Tool();
		~Tool();
		int get_number_of_uses() const;
		const Worker *get_owner() const;
		void set_owner(Worker *owner);
		virtual void use() = 0;
};

std::ostream &operator<<(std::ostream &o, const Tool &t);

# include "Worker.hpp"

#endif
