#pragma once

#include "edge.hpp"

#include <functional>
#include <list>

namespace algo
{
	class graph
	{
	public:
		using vertex_ptrs = std::list<vertex_ptr>;
		using edge_ptrs = std::vector<edge_ptr>;
	private:
		edge_ptrs _edges;
		vertex_ptrs _vertices;
	public:
		graph();
		graph(const graph&) = delete;
		graph(graph&&) = default;
		graph &operator=(const graph&) = delete;
		graph &operator=(graph&&) = delete;
		virtual ~graph() = default;

		vertex_ptrs &vertices();
		const vertex_ptrs &vertices() const;
		edge_ptrs &edges();
		const edge_ptrs &edges() const;
		vertex_ptr find(const vertex &v) const;
		edge_ptr find(const edge &e) const;
		edge_ptr find(const vertex &v, const vertex &u) const;
		bool contains(const vertex &v) const;
		bool contains(const edge &e) const;
		void assert_contains(const vertex &v) const;
		void assert_contains(const edge &e) const;
		bool isolated(const vertex &v) const;
		bool non_isolated(const vertex &v) const;
		bool is_connected() const;
		edge_ref_set adj_edges(const vertex &v) const;
		void insert_vertex(vertex_ptr vertex);
		void insert_edge(edge_ptr edge);
	private:
		bool _non_isolated(const vertex &v) const;
		virtual bool incident(const edge &e, const vertex &u) const;
		virtual bool validate(const vertex &v) const;
		virtual bool validate(const edge &e) const;
	};

	
	using weight_function = std::function<float(const edge&)>;
	
	// a graph that has a weight function for its edges
	class weighted_graph : virtual public graph
	{
		weight_function _w;
	public:
		weighted_graph();
		weighted_graph(weight_function w);
		weighted_graph(const weighted_graph&) = delete;
		weighted_graph(weighted_graph&&) = default;
		weighted_graph &operator=(const weighted_graph&) = delete;
		weighted_graph &operator=(weighted_graph&&) = delete;
		virtual ~weighted_graph() = default;
		
		void set_w(weight_function w);
		const weight_function &w() const;
	};
	
	// a graph suitable for single-source shortest-path problem
	class single_source_shortest_path_graph : virtual public weighted_graph
	{
	protected:
		vertex *_source;
		vertex *_destination;
	public:
		single_source_shortest_path_graph();
		single_source_shortest_path_graph(const single_source_shortest_path_graph&) = delete;
		single_source_shortest_path_graph(single_source_shortest_path_graph&&) = default;
		single_source_shortest_path_graph &operator=(const single_source_shortest_path_graph&) = delete;
		single_source_shortest_path_graph &operator=(single_source_shortest_path_graph&&) = delete;
		virtual ~single_source_shortest_path_graph() = default;

		vertex *get_source() const;
		void set_source(vertex &v);
		vertex *get_destination() const;
		void set_destination(vertex &v);
	};

	// a weighted graph whose edges have time-dependent availability
	// and vertices can incur individual delays
	class time_dependent_graph : virtual public weighted_graph
	{
		float _time_offset;
	public:
		time_dependent_graph(float time_offset = 0, weight_function w = [](const edge&){ return (0); });
		time_dependent_graph(const time_dependent_graph&) = delete;
		time_dependent_graph(time_dependent_graph&&) = default;
		time_dependent_graph &operator=(const time_dependent_graph&) = delete;
		time_dependent_graph &operator=(time_dependent_graph&&) = delete;
		virtual ~time_dependent_graph() = default;

		void set_time_offset(float time_offset);
		float get_time_offset() const;
	private:
		bool validate(const edge &e) const override;
		bool validate(const vertex &v) const override;
		bool incident(const edge &e, const vertex &u) const override;
		virtual float compute_delay(const delay_vertex &dv) const;
	};

	// a weighted graph suitable for SSSP with a source and destination vertices,
	// whose edges have time-dependent availability and vertices can incur individual delays
	class dijkstra_graph : public single_source_shortest_path_graph, public time_dependent_graph
	{
	public:
		dijkstra_graph(float time_offset = 0, weight_function w = [](const edge&){ return (0); });
		dijkstra_graph(const dijkstra_graph&) = delete;
		dijkstra_graph(dijkstra_graph&&) = default;
		dijkstra_graph &operator=(const dijkstra_graph&) = delete;
		dijkstra_graph &operator=(dijkstra_graph&&) = delete;
		~dijkstra_graph() = default;
	private:
		float compute_delay(const delay_vertex &dv) const override;
	};
}
