#pragma once

#include "algorithm.hpp"

namespace sim
{
	class node : public algo::delay_vertex
	{
		std::string _name;
	public:
		node(std::string name);
		node() = delete;
		node(const node&) = default;
		node(node&&) = default;
		node &operator=(const node&) = default;
		node &operator=(node&&) = default;
		~node() = default;

		const std::string &get_name() const;
		
		bool operator<(const sim::node &rhs) const;
	};

	using node_ptr = std::shared_ptr<node>;
}
