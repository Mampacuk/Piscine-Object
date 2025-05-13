#include "graph.hpp"

#include <algorithm>
#include <cassert>

namespace algo
{
	// GRAPH
	graph::graph() : _edges(), _vertices() {}

	graph::vertex_ptrs &graph::vertices() { return (_vertices); }
	const graph::vertex_ptrs &graph::vertices() const { return (_vertices); }
	graph::edge_ptrs &graph::edges() { return (_edges); }
	const graph::edge_ptrs &graph::edges() const { return (_edges); }
	
	vertex_ptr graph::find(const vertex &v) const
	{
		if (auto v_it = std::find_if(_vertices.begin(), _vertices.end(),
			[&v](const vertex_ptr &v_ptr) { return (v == *v_ptr); }); v_it != _vertices.end())
			return (*v_it);
		return (nullptr);
	}

	edge_ptr graph::find(const edge &e) const
	{
		if (auto e_it = std::find_if(_edges.begin(), _edges.end(),
			[&e](const edge_ptr &e_ptr) { return (e == *e_ptr); }); e_it != _edges.end())
			return (*e_it);
		return (nullptr);
	}

	edge_ptr graph::find(const vertex &v, const vertex &u) const
	{
		if (auto e_it = std::find_if(_edges.begin(), _edges.end(),
			[&v, &u](const edge_ptr &e_ptr) { return (e_ptr->contains(u) && e_ptr->contains(v)); });
			e_it != _edges.end())
			return (*e_it);
		return (nullptr);
	}

	bool graph::contains(const vertex &v) const
	{
		return (std::find_if(_vertices.begin(), _vertices.end(),
				[&v](const vertex_ptr &v_ptr) { return (v == *v_ptr); }) != _vertices.end());
	}

	bool graph::contains(const edge &e) const
	{
		return (std::find_if(_edges.begin(), _edges.end(),
				[&e](const edge_ptr &e_ptr) { return (e == *e_ptr); }) != _edges.end());
	}

	void graph::assert_contains(const vertex &v) const
	{
		assert(contains(v));
	}

	void graph::assert_contains(const edge &e) const
	{
		assert(contains(e));
	}

	bool graph::non_isolated(const vertex &v) const
	{
		assert_contains(v);
		return (_non_isolated(v));
	}

	bool graph::_non_isolated(const vertex &v) const
	{
		return (std::any_of(_edges.begin(), _edges.end(), 
							[&v](const edge_ptr &e_ptr) { return (e_ptr && e_ptr->contains(v)); }));
	}

	bool graph::incident(const edge &e, const vertex &u) const
	{
		return (e.contains(u));
	}

	bool graph::validate(const vertex&) const { return (true); }
	bool graph::validate(const edge&) const { return (true); }

	bool graph::isolated(const vertex &v) const
	{
		return (!non_isolated(v));
	}

	bool graph::is_connected() const
	{
		return (std::all_of(_vertices.begin(), _vertices.end(),
							[this](const vertex_ptr &v_ptr) { return (v_ptr && _non_isolated(*v_ptr)); }));
	}

	edge_ref_set graph::adj_edges(const vertex &v) const
	{
		assert_contains(v);
		edge_ref_set res;
		for (auto &e : _edges)
			if (incident(*e, v))
				res.insert(*e);
		return (res);
	}

	void graph::insert_vertex(vertex_ptr vertex)
	{
		if (vertex && !contains(*vertex) && validate(*vertex))
			_vertices.push_back(std::move(vertex));
	}

	void graph::insert_edge(edge_ptr edge)
	{
		if (edge && !contains(*edge) && validate(*edge))
		{
			assert_contains(edge->first());
			assert_contains(edge->second());
			_edges.push_back(std::move(edge));
		}
	}

	// WEIGHTED GRAPH
	weighted_graph::weighted_graph() : graph(), _w() {}
	weighted_graph::weighted_graph(weight_function w) : graph(), _w(std::move(w)) {}

	void weighted_graph::set_w(weight_function w)
	{
		_w = std::move(w);
	}

	const weight_function &weighted_graph::w() const
	{
		return (_w);
	}

	// SINGLE-SOURCE SHORTEST-PATH GRAPH
	single_source_shortest_path_graph::single_source_shortest_path_graph() : _source(nullptr), _destination(nullptr) {}
	vertex *single_source_shortest_path_graph::get_source() const { return (_source); }
	vertex *single_source_shortest_path_graph::get_destination() const { return (_destination); }
	void single_source_shortest_path_graph::set_source(vertex &v) { assert_contains(v); _source = &v; }
	void single_source_shortest_path_graph::set_destination(vertex &v) { assert_contains(v); _destination = &v; }

	// TIME-DEPENDENT GRAPH
	time_dependent_graph::time_dependent_graph(float time_offset, weight_function w) : weighted_graph(std::move(w)), _time_offset(time_offset) {}

	void time_dependent_graph::set_time_offset(float time_offset)
	{
		_time_offset = time_offset;
	}

	float time_dependent_graph::get_time_offset() const
	{
		return (_time_offset);
	}

	bool time_dependent_graph::validate(const edge &e) const
	{
		(void)dynamic_cast<const time_dependent_edge&>(e);
		return (true);
	}

	bool time_dependent_graph::validate(const vertex &e) const
	{
		(void)dynamic_cast<const delay_vertex&>(e);
		return (true);
	}

	bool time_dependent_graph::incident(const edge &e, const vertex &u) const
	{
		if (!e.contains(u))
			return (false);
		const float u_d = _time_offset + u.get_d() + compute_delay(dynamic_cast<const delay_vertex&>(u));
		return (dynamic_cast<const time_dependent_edge&>(e).available({u_d, u_d + w()(e)}));
 	}

	float time_dependent_graph::compute_delay(const delay_vertex &dv) const
	{
		return (dv.get_delay());
	}

	// DIJKSTRA GRAPH
	dijkstra_graph::dijkstra_graph(float time_offset, weight_function w) : time_dependent_graph(time_offset, w) {}

	float dijkstra_graph::compute_delay(const delay_vertex &dv) const
	{
		float accumulated_delay = dynamic_cast<delay_vertex&>(*_source).get_delay();
		const delay_vertex *curr = &dv;
		while (curr && curr != _source)
		{
			accumulated_delay += curr->get_delay();
			curr = dynamic_cast<delay_vertex*>(curr->get_pi());
		}
		return (accumulated_delay);
	}
}
