#pragma once
#include "common.hpp"

#include "vertex.hpp"

namespace algo
{
	class edge
	{
		vertex &_first;
		vertex &_second;
	public:
		edge(vertex &first, vertex &second);
		edge() = delete;
		edge(const edge&) = default;
		edge(edge&&) = default;
		edge &operator=(const edge&) = delete;
		edge &operator=(edge&&) = delete;
		virtual ~edge() = default;

		vertex &first() const;
		vertex &second() const;
		bool contains(const vertex &v) const;
		vertex &other(const vertex &v) const;
		bool operator==(const edge &rhs) const;
		bool operator<(const edge &rhs) const;
	};

	using edge_ptr = std::shared_ptr<edge>;
	using edge_ref = std::reference_wrapper<edge>;
	using edge_ref_set = std::set<edge_ref, std::less<edge>>;

	class time_dependent_edge : public edge
	{
	public:
		using booking = std::pair<float, float>;
		using bookings = std::vector<booking>;

		time_dependent_edge(vertex &first, vertex &second);
		time_dependent_edge() = delete;
		time_dependent_edge(const time_dependent_edge&) = default;
		time_dependent_edge(time_dependent_edge&&) = default;
		time_dependent_edge &operator=(const time_dependent_edge&) = delete;
		time_dependent_edge &operator=(time_dependent_edge&&) = delete;
		~time_dependent_edge() = default;

		void book(booking time);
		bool available(booking time) const;
	private:
		bookings _bookings;
	};
}
