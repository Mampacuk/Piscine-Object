#pragma once
#include "common.hpp"

#include "graph.hpp"

#include <stdexcept>

namespace algo
{
	// vedge (vertices with edge between them): holds e(u, v)
	struct vedge
	{
		vertex& u;
		edge& e;
		vertex& v;
	};

	using path = std::list<vedge>;

	void init_single_source(const graph &g, vertex &src);
	void relax(const edge &e, const weight_function &w, bool swap = false);
	void dijkstra(const dijkstra_graph &g);
	void dijkstra(const graph &g, const weight_function &w, vertex &src, vertex *dest = nullptr);
	path construct_path(const single_source_shortest_path_graph &g);

	class algorithmic_error : public std::runtime_error
	{
	public:
		algorithmic_error(const std::string &what_arg);
		algorithmic_error(const char *what_arg);
	};
}
