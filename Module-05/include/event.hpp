#pragma once
#include "common.hpp"

namespace sim
{
	class event
	{
	public:
		virtual void execute() const = 0;
		virtual ~event() = default;
	};

	class increase_node_delay : public event
	{
		node &_node;
		time_unit _delay;
	public:
		increase_node_delay() = delete;
		increase_node_delay(node &n, time_unit delay);
		increase_node_delay(const increase_node_delay&) = default;
		increase_node_delay(increase_node_delay&&) = default;
		increase_node_delay& operator=(const increase_node_delay&) = default;
		increase_node_delay& operator=(increase_node_delay&&) = default;
		~increase_node_delay() = default;

		void execute() const override;
	};
}
