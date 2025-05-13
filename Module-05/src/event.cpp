#include "event.hpp"

#include "logging.hpp"
#include "node.hpp"

namespace sim
{
	increase_node_delay::increase_node_delay(node &n, time_unit delay)
	: _node(n), _delay(delay)
	{
		logging::info("Created event: node \"" +  _node.get_name() + "\" delay increase by " + std::to_string(_delay) + "mins");
	}
	
	void increase_node_delay::execute() const
	{
		_node.set_delay(_node.get_delay() + _delay);
	}
}
