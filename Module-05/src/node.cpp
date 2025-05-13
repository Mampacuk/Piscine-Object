#include "node.hpp"

namespace sim
{
	node::node(std::string name) : _name(std::move(name)) {}

	const std::string &node::get_name() const
	{
		return (_name);
	}
	
	bool node::operator<(const sim::node &rhs) const
	{
		return (_name < rhs.get_name());
	}
}
