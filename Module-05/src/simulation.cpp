#include "simulation.hpp"

#include "algorithm.hpp"
#include "constants.hpp"
#include "math.hpp"
#include "util.hpp"

#include <algorithm>
#include <fstream>
#include <numeric>
#include <random>
#include <sstream>

// to delete
#include <iostream>

namespace sim
{
	void simulation::insert_train(train new_train)
	{
		if (std::find_if(_trains.begin(), _trains.end(),
						 [&new_train](const train &t) { return (new_train.get_name() == t.get_name()); }) != _trains.end())
			throw std::invalid_argument("Duplicate trains are not allowed");
		_trains.push_back(std::move(new_train));
	}

	void simulation::insert_railroad(railroad new_railroad)
	{
		if (_network.find(new_railroad))
			throw std::invalid_argument("Duplicate railroads are not allowed");
		_network.insert_edge(std::make_shared<railroad>(new_railroad));
	}

	void simulation::insert_node(node new_node)
	{
		if (find_node(new_node.get_name()))
			throw std::invalid_argument("Duplicate nodes are not allowed");
		_network.insert_vertex(std::make_shared<node>(new_node));
	}

	node_ptr simulation::find_node(const std::string &name, bool throw_exception)
	{
		if (auto node_it = std::find_if(_network.vertices().begin(), _network.vertices().end(),
										[&name](algo::vertex_ptr &v_ptr)
												{ if (node_ptr n_ptr = std::dynamic_pointer_cast<node>(v_ptr))
													return (name == n_ptr->get_name());
												  return (false); });
			node_it != _network.vertices().end())
			return (std::dynamic_pointer_cast<node>(*node_it));
		else if (throw_exception)
			throw std::invalid_argument("Couldn't find a node named \"" + name + "\" in simulation");
		return (nullptr);
	}

	// return true if node section was completed and rail section has started
	bool simulation::parse_node_definition(std::istringstream &iss)
	{
		std::string node_token, node_name_token, trailing_token;
		if (!(iss >> node_token >> node_name_token))
			throw parsing_error("Failed to parse a node definition in rail network file");
		if (node_token == consts::strs::rail_token)
			return (parse_railroad_definition(iss, node_name_token));
		else if (node_token != consts::strs::node_token)
			throw parsing_error("Expected a \"Node\" token at the start of line in the node section");
		else if (!!(iss >> trailing_token))
			throw parsing_error("Extra tokens in a node definition in rail network file");
		insert_node(node(node_name_token));
		return (false);
	}

	bool simulation::parse_railroad_definition(std::istringstream &iss, std::optional<std::string> first_node_token)
	{
		std::string rail_token, first_node_name, second_node_name, trailing_token;
		float length, speed_limit;
		if (first_node_token)
		{
			rail_token = consts::strs::rail_token;
			first_node_name = *first_node_token;
			if (!(iss >> second_node_name >> length >> speed_limit))
				throw parsing_error("Failed to parse a rail definition in rail network file");
		}
		else if (!(iss >> rail_token >> first_node_name >> second_node_name >> length >> speed_limit))
			throw parsing_error("Failed to parse a rail definition in rail network file");
		if (rail_token != consts::strs::rail_token)
			throw parsing_error("Expected a \"Rail\" token at the start of line in the rail section");
		else if (!!(iss >> trailing_token))
			throw parsing_error("Extra tokens in a railroad definition in rail network file");
		else if (length < consts::sim::min_railroad_length)
			throw parsing_error("Railroad too short (minimum is 1km)");
		insert_railroad(railroad(*find_node(first_node_name, true), *find_node(second_node_name, true), math::kilo * length, speed_limit));
		return (true);
	}

	void simulation::parse_train_definition(std::istringstream iss)
	{
		std::string train_name, source_node_name, destination_node_name, departure_time, stop_duration, trailing_token;
		float mass, friction, accel_force, decel_force;
		if (!(iss >> train_name >> mass >> friction >> accel_force >> decel_force >> source_node_name >> destination_node_name >>
			  departure_time >> stop_duration))
			throw parsing_error("Failed to parse a train definition in train composition file");
		else if (!!(iss >> trailing_token))
			throw parsing_error("Extra tokens in a train definition in train composition file");
		insert_train(train(train_name, math::kilo * mass, friction, math::kilo * accel_force, math::kilo * decel_force,
						   *find_node(source_node_name, true), *find_node(destination_node_name, true), util::extract_mins(departure_time),
						   util::extract_mins(stop_duration)));
	}

	simulation::simulation(const char *rail_network, const char *train_composition)
	{
		{
			std::ifstream network_config(rail_network);
			if (!network_config.is_open())
				throw parsing_error("Failed to open rail network file \"" + std::string(rail_network) + "\"");
			std::string line;
			bool node_section_complete = false;
			while (std::getline(network_config, line))
			{
				std::istringstream iss(line);
				if (!node_section_complete)
					node_section_complete = parse_node_definition(iss);
				else
					parse_railroad_definition(iss);
			}
			if (!_network.is_connected())
				throw parsing_error("Network is supposed to be connected");
		}
		{
			std::ifstream train_config(train_composition);
			if (!train_config.is_open())
				throw parsing_error("Failed to open train composition file \"" + std::string(train_composition) + "\"");
			std::string line;
			while (std::getline(train_config, line))
				parse_train_definition(std::istringstream(line));
		}
	}

	void simulation::run()
	{
		// generate events
		_events.clear();
		for (auto &vertex : _network.vertices())
			if (event_happens())
				_events.push_back(std::make_unique<sim::increase_node_delay>(dynamic_cast<node&>(*vertex), consts::sim::event_duration));
		// sort trains according their departure time
		_trains.sort([](const train &a, const train &b)
					 { return (a.get_departure_time() < b.get_departure_time()); });
		// compute shortest paths for each train
		for (auto &train : _trains)
		{
			for (auto &vertex : _network.vertices())  // set individual train delays
				dynamic_cast<algo::delay_vertex&>(*vertex).set_delay(train.get_stop_duration());
			for (auto &event : _events)  // execute events that incur additional delays
				event->execute();
			_network.set_time_offset(train.get_departure_time());
			_network.set_source(train.get_source());
			_network.set_destination(train.get_destination());
			_network.set_w([&train](const algo::edge &e)
						   { return (train.compute_travel_time(dynamic_cast<const railroad&>(e))); });
			algo::dijkstra(_network);
			if (train.get_destination().get_pi() == nullptr)
				throw algo::algorithmic_error("No path was found for train \"" + train.get_name() + "\"");
			train.set_path(cast_path(algo::construct_path(_network)));
			train.book_path();
			// debug
			std::cout << "train " << train.get_name() << " path:" << std::endl;
			for (auto &[u, e, v] : train.get_path())
				std::cout << u.get_name() << " -> " << v.get_name() << std::endl;
			// debug //
			log_train_journey(train);
		}
	}

	void simulation::log_train_journey(const train &t) const
	{
		std::ofstream file(t.get_name() + consts::strs::_ + util::convert_mins(t.get_departure_time()) + consts::strs::result_ext);
		if (!file)
			throw std::runtime_error("Failed to create train " + t.get_name() + "'s output file");
		file << "Train : " << t.get_name() << std::endl;
		file << "Final travel time : " << util::convert_mins(t.get_arrival_time()) << std::endl;
		const path &p = t.get_path();
		const float journey_length = std::accumulate(p.begin(), p.end(), 0.f, [](float sum, const connection &c) { return (sum + c.r.get_length()); });
		float time_spent = 0.f;
		float distance_covered = 0.f;
		for (auto &[u, r, v] : p)
		{
			train::events events;
			const float railroad_start_time = time_spent;
			const float railroad_start_distance = distance_covered;
			const float railroad_travel_time = t.compute_travel_time(r, &events);
			const float railroad_length = r.get_length();
			time_spent += u.get_delay();
			// debug
			std::cout << "describing railroad (" << u.get_name() << ", " << v.get_name() << ")" << std::endl;
			std::cout << "events distances: ";
			for (const auto &e : events)
				std::cout << "{" << train::event::to_string(e.event_type) << ":" << e.distance << "} ";
			std::cout << std::endl;
			// debug
			for (const auto &e : events)
			{
				file << "[" << util::convert_mins(railroad_start_time + e.time) << "] - [" << u.get_name() << "][" << v.get_name() << "] - ["
					 << (journey_length - railroad_start_distance - e.distance) << "km] - [" << train::event::to_string(e.event_type) << "] - ";
				const size_t number_of_segments = std::ceil(railroad_length / consts::sim::railroad_segment_length);
				// std::cout << "segments: " << number_of_segments << ", e.distance=" << e.distance << 
				for (size_t i = 0; i < number_of_segments; i++)
				{
					if ((e.distance >= i * consts::sim::railroad_segment_length && e.distance < (i + 1) * consts::sim::railroad_segment_length)
						|| (e.event_type == train::event::type::stopped && i == number_of_segments - 1))
						file << "[x]";
					else
					{
						// debug
						// if (e.event_type == train::event::type::braking || e.event_type == train::event::type::maintain || e.event_type == train::event::type::stopped)
						// std::cout << "(" << train::event::to_string(e.event_type) << ") block " << i << "/" << number_of_segments << " was displayed as [] because it's not the case that " 
						// 			<< i << "*" << consts::sim::railroad_segment_length << "=" << i * consts::sim::railroad_segment_length
						// 			<< " <= e.distance=" << e.distance << " < " << i + 1 << " * " << consts::sim::railroad_segment_length << "="
						// 			<< (i + 1) * consts::sim::railroad_segment_length << std::endl;
						// debug
						file << "[ ]";
					}
				}
				file << std::endl;
			}
			// debug
			// std::cout << std::endl;
			// debug
			time_spent += railroad_travel_time;
			distance_covered += railroad_length;
		}
	}

	bool simulation::event_happens() const
	{
		static std::random_device rd;
		static std::mt19937 gen{rd()};
		static std::bernoulli_distribution happen{consts::sim::event_probability};
		return (happen(gen));
	}

	path cast_path(algo::path journey)
	{
		path res;
		for (auto &[u, e, v] : journey)
			res.emplace_back(connection{ dynamic_cast<node&>(u), dynamic_cast<railroad&>(e), dynamic_cast<node&>(v) });
		return (res);
	}

	parsing_error::parsing_error(const std::string &what_arg) : std::runtime_error(what_arg) {}
	parsing_error::parsing_error(const char *what_arg) : std::runtime_error(what_arg) {}
}
