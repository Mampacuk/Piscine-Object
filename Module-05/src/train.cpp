#include "train.hpp"

#include "constants.hpp"
#include "math.hpp"
#include "node.hpp"
#include "railroad.hpp"

#include <cassert>
#include <cmath>
#include <iterator>
#include <optional>

// to delete
#include <iostream>

namespace
{
	// expects a speed-up event in the beginning, and a stopped event at the end.
	void insert_milestones(sim::train::events &events, float accel, float decel, float vmax, std::optional<float> vpeak)
	{
		if (events.empty() || events.front().event_type != sim::train::event::type::speedup || events.back().event_type != sim::train::event::type::stopped)
			return ;
		sim::train::events::iterator curr_event = events.begin();
		float curr_distance = consts::sim::railroad_segment_length;
		while (curr_event->event_type != sim::train::event::type::stopped)
		{
			auto next_event = std::next(curr_event);
			while (curr_distance < next_event->distance)
			{
				float a = 0.f, v0 = 0.f;
				switch (curr_event->event_type)
				{
					case sim::train::event::type::speedup:
						a = accel;
						break ;
					case sim::train::event::type::maintain:
						v0 = vmax;
						break ;
					case sim::train::event::type::braking:
						a = -decel;
						v0 = vpeak.value_or(vmax);
						break ;
					default:
						throw std::runtime_error("Unrecognized sim::train::event::type enum value");
				}
				// distance from curr. event to milestone
				float ds = curr_distance - curr_event->distance;
				// solve 1/2 a t^2 + v0 t − ds = 0 for t >= 0
				float t_offset;
				if (std::fabs(a) < math::negligible_acceleration)
					t_offset = ds / v0;  // no acceleration => pure constant-speed => t = ds / v0
				else
				{
					// quadratic formula
					const float A = 0.5f * a;
					const float B = v0;
					const float C = -ds;
					const float D = B * B - 4 * A * C;
					assert(D >= 0.0f);
					const float sqrtD = std::sqrt(D);

					// two roots; pick the positive one
					const float t1 = (-B + sqrtD) / (2 * A);
					const float t2 = (-B - sqrtD) / (2 * A);
					t_offset = (t1 >= 0.0f ? t1 : t2);
					assert(t_offset > 0.0f);
				}
				// absolute event time = segment-start time + offset
				assert(events.emplace(next_event, curr_event->event_type, curr_event->time + t_offset, curr_distance)->time < next_event->time);
				curr_distance += consts::sim::railroad_segment_length;
			}
			curr_event = next_event;
		}
	}

	float travel_time(float accel,	/* km/min^2 */
					  float decel,	/* km/min^2 */
					  float length, /* km */
					  float speed_limit /* km/min */,
					  sim::train::events *events = nullptr)
	{
		assert(accel > 0.f);
		assert(decel > 0.f);
		assert(length > 0.f);
		assert(speed_limit > 0.f);
		if (events)
			events->emplace_back(sim::train::event::type::speedup, 0.f, 0.f);
		// distance to accelerate from v=0 to v=vmax
		const float s_a = (speed_limit * speed_limit) / (2.0f * accel);
		assert(s_a > 0.f);
		// distance to decelerate from v=vmax to v=0
		const float s_d = (speed_limit * speed_limit) / (2.0f * decel);
		assert(s_d > 0.f);
		std::optional<float> v_p;
		float total_time = 0.0f;
		if (s_a + s_d <= length)
		{
			// case 1: we can reach speed_limit (vmax) and cruise
			const float t_a = speed_limit / accel;	// time to accelerate from v=0 to v=vmax
			const float t_d = speed_limit / decel;	// time to decelerate from v=vmmax to v=0
			const float s_c = length - s_a - s_d;	// distance to cruise at v=vmax
			const float t_c = s_c / speed_limit;	// time to cruise at v=vmax
			total_time = t_a + t_c + t_d;			// sum of accel., decel. and cruising times
			if (events)
			{
				events->emplace_back(sim::train::event::type::maintain, t_a, s_a);
				events->emplace_back(sim::train::event::type::braking, t_a + t_c, s_a + s_c);
			}
		}
		else
		{
			// case 2: we can't reach speed_limit (vmax), compute peak speed vpeak
			v_p = std::sqrt(2.0f * accel * decel * length / (accel + decel));	// vpeak
			const float s_p = (*v_p * *v_p) / (2.0f * accel);									// distance to reach vpeak
			const float t_a = *v_p / accel;													// time to accelerate from v=0 to v=vpeak
			const float t_d = *v_p / decel;													// time to decelerate from v=vpeak to v=0
			total_time = t_a + t_d;															// sum of accel. and decel. times
			if (events)
				events->emplace_back(sim::train::event::type::braking, t_a, s_p);
		}
		if (events)
		{
			events->emplace_back(sim::train::event::type::stopped, total_time, length);
			insert_milestones(*events, accel, decel, speed_limit, std::move(v_p));
		}
		return (total_time);
	}
}

namespace sim
{
	size_t train::_global_id = 0;

	train::train(std::string name, float mass /* kg */, float friction_coeff, float accel_force /* Newtons */,
				 float decel_force /* Newtons */, node &from, node &to, time_unit departure_time, time_unit stop_time)
	: _id(_global_id++), _name(std::move(name)),
	  _accel(math::acceleration_with_friction(accel_force, mass, friction_coeff) * math::m_s2_to_km_min2),
	  _decel(math::acceleration_with_friction(decel_force, mass, friction_coeff) * math::m_s2_to_km_min2),
	  _from(from), _to(to), _departure_time(departure_time), _stop_time(stop_time)
	{
		if (_accel < 0.f)
			throw std::runtime_error("Acceleration is negative for train " + _name + " (" + std::to_string(_accel) + ")");
		if (_decel < 0.f)
			throw std::runtime_error("Deceleration is negative for train " + _name + " (" + std::to_string(_decel) + ")");
	}

	const std::string &train::get_name() const
	{
		return (_name);
	}

	float train::get_acceleration() const
	{
		return (_accel);
	}

	float train::get_deceleration() const
	{
		return (_decel);
	}

	time_unit train::get_departure_time() const
	{
		return (_departure_time);
	}

	time_unit train::get_arrival_time() const
	{
		return (_arrival_time);
	}

	time_unit train::get_stop_duration() const
	{
		return (_stop_time);
	}

	void train::set_path(path journey)
	{
		_path = std::move(journey);
	}

	const path &train::get_path() const
	{
		return (_path);
	}

	void train::book_path()
	{
		float time = _departure_time;
		for (auto &[u, e, v] : _path)
		{
			const float delayed_time = time + u.get_delay();
			const float travel_time = compute_travel_time(e);
			e.book({delayed_time, delayed_time + travel_time});
			time = delayed_time + travel_time;
		}
		_arrival_time = time_unit(time);
	}

	node &train::get_source() const
	{
		return (_from);
	}

	node &train::get_destination() const
	{
		return (_to);
	}

	float train::compute_travel_time(const railroad &r, events *events) const
	{
		return (travel_time(_accel, _decel, r.get_length(), r.get_speed_limit(), events));
	}

	train::event::event(type event_type, float time, float distance) : event_type(event_type), time(time), distance(distance) {}

	std::string train::event::to_string(type et)
	{
		switch (et)
		{
			case type::speedup:
				return ("Speed up");
			case type::maintain:
				return ("Maintain");
			case type::braking:
				return ("Braking");
			case type::stopped:
				return ("Stopped");
			default:
				throw std::runtime_error("Unrecognized sim::train::event::type enum value");
		}
	}
}
