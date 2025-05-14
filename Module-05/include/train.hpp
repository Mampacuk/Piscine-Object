#pragma once
#include "common.hpp"

#include "algorithm.hpp"

#include <string>

namespace sim
{
	class train
	{
		size_t _id;
		std::string _name;
		float _accel;  // km/min^2
		float _decel;  // km/min^2
		node &_from;
		node &_to;
		time_unit _departure_time;
		time_unit _stop_time;
		time_unit _arrival_time;
		path _path;

		static size_t _global_id;
	public:
		train(std::string name, float mass /* kg */, float friction_coeff, float accel_force /* Newtons */,
			  float decel_force /* Newtons */, node &from, node &to, time_unit departure_time, time_unit stop_time);
		train() = delete;
		train(const train&) = default;
		train(train&&) = default;
		train& operator=(const train&) = delete;
		train& operator=(train&&) = delete;
		~train() = default;

		void set_path(path journey);
		const path &get_path() const;
		void book_path();
		const std::string &get_name() const;
		float get_acceleration() const;
		float get_deceleration() const;
		time_unit get_departure_time() const;
		time_unit get_arrival_time() const;
		time_unit get_stop_duration() const;
		node &get_source() const;
		node &get_destination() const;
		
		struct event
		{
			enum class type
			{
				speedup,
				maintain,
				braking,
				stopped
			};
			
			type event_type;
			float time;
			float distance;

			event(type event_type, float time, float distance);

			static std::string to_string(type et);
		};
		
		using events = std::list<event>;

		float compute_travel_time(const railroad &r, events *events = nullptr) const;
	};
}
