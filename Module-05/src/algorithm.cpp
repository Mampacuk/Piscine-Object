#include "algorithm.hpp"

#include <limits>

// to delete
#include <iostream>
#include "simulation.hpp"

namespace algo
{
	void init_single_source(const graph &g, vertex &src)
	{
		g.assert_contains(src);
		for (auto &v : g.vertices())
		{
			v->d() = std::numeric_limits<float>::infinity();
			v->pi() = nullptr;
		}
		src.d() = 0;
	}

	void relax(const edge &e, const weight_function &w, bool swap)
	{
		vertex &u = swap ? e.second() : e.first();
		vertex &v = swap ? e.first() : e.second();
		const float weight = w(e);
		if (v.d() > u.d() + weight)
		{
			v.d() = u.d() + weight;
			v.pi() = &u;
		}
	}

	namespace
	{
		struct less_d
		{
			bool operator()(const vertex_ptr &lhs, const vertex_ptr &rhs) const
			{
				if (lhs->get_d() != rhs->get_d())
					return (lhs->get_d() < rhs->get_d());
				return (lhs.get() < rhs.get());
			}
		};
	}

	void dijkstra(const graph &g, const weight_function &w, vertex &src, vertex *dest)
	{
		init_single_source(g, src);
		graph::vertex_ptrs q = g.vertices();
		q.sort(less_d());
		// std::cout << "STARTING DIJSKTRA, Q.SIZE=" << q.size() << std::endl << std::endl;
		while (!q.empty())
		{
			vertex &u = *q.front();
			q.pop_front();
			////////////////
			// const sim::node &n = dynamic_cast<const sim::node&>(u);
			// std::cout << "popped node=" << n.get_name() << ", d=" << n.get_d() << " from the queue" << std::endl << std::endl;
			////////////////
			if (&u == dest)
			{
				// std::cout << "REACHED DEST WITH " << q.size() << " NODES REMAINING" << std::endl;
				return ;
			}
			for (auto &e : g.adj_edges(u))
			{
				///////////////////
				const sim::node &other = dynamic_cast<const sim::node&>(e.get().other(u));
				// const sim::railroad &r = dynamic_cast<const sim::railroad&>(e.get());
				// std::cout << "determined incidence (" << n.get_name() << ", " << other.get_name() << ")" << std::endl;
				// std::cout << "before relaxing, " << other.get_name() << " d was " << other.get_d() << std::endl;
				//////////////////
				const float pre_relax = other.get_d();
				relax(e, w, u != e.get().first());
				const float post_relax = other.get_d();
				// std::cout << "after relaxing, " << other.get_name() << " d became " << other.get_d() << std::endl << std::endl;
				if (pre_relax != post_relax)
					q.sort(less_d());
			}
		}
	}

	void dijkstra(const dijkstra_graph &g)
	{
		dijkstra(g, g.w(), *g.get_source(), g.get_destination());
	}

	path construct_path(const single_source_shortest_path_graph &g)
	{
		path res;
		vertex *curr = g.get_destination();
		for (; curr != g.get_source(); curr = curr->pi())
			res.emplace_front(vedge{ *curr->pi(), *g.find(*curr, *curr->pi()), *curr });
		return (res);
	}

	algorithmic_error::algorithmic_error(const std::string &what_arg) : std::runtime_error(what_arg) {}
	algorithmic_error::algorithmic_error(const char *what_arg) : std::runtime_error(what_arg) {}
}
