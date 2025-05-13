#pragma once

#include <memory>
#include <set>

namespace algo
{
	class vertex
	{
		vertex *_pi;  // predecessor
		float _d;  // shortest-path estimate
	public:
		vertex();
		vertex(const vertex&) = default;
		vertex(vertex&&) = default;
		vertex &operator=(const vertex&) = default;
		vertex &operator=(vertex&&) = default;
		virtual ~vertex() = default;
		
		vertex *&pi();
		vertex *get_pi() const;
		float &d();
		constexpr float get_d() const { return (_d); }

		bool operator==(const vertex &rhs) const;
		bool operator!=(const vertex &rhs) const;
		bool operator<(const vertex &rhs) const;
	};

	class delay_vertex : public vertex
	{
		float _delay;
	public:
		delay_vertex();
		delay_vertex(float delay);
		delay_vertex(const delay_vertex&) = default;
		delay_vertex(delay_vertex&&) = default;
		delay_vertex &operator=(const delay_vertex&) = default;
		delay_vertex &operator=(delay_vertex&&) = default;
		virtual ~delay_vertex() = default;

		float get_delay() const;
		void set_delay(float delay);
	};

	using vertex_ptr = std::shared_ptr<vertex>;
	using vertex_ref = std::reference_wrapper<vertex>;
	using vertex_ref_set = std::set<vertex_ref, std::less<vertex>>;
}
