#pragma once

#include "algorithm.hpp"
#include "event.hpp"
#include "node.hpp"
#include "railroad.hpp"
#include "train.hpp"

#include <optional>

namespace sim
{
	class simulation
	{
	public:
		simulation(const char *rail_network, const char *train_composition);
		simulation() = delete;
		simulation(const simulation &) = delete;
		simulation(simulation &&) = default;
		simulation &operator=(const simulation &) = delete;
		simulation &operator=(simulation &&) = delete;
		~simulation() = default;

		void run();
	private:
		using trains = std::list<train>;
		using events = std::vector<std::unique_ptr<event>>;

		algo::dijkstra_graph _network;
		trains _trains;
		events _events;

		node_ptr find_node(const std::string &name, bool throw_exception = false);
		void insert_train(train new_train);
		void insert_railroad(railroad new_railroad);
		void insert_node(node new_node);
		bool parse_node_definition(std::istringstream &iss);
		bool parse_railroad_definition(std::istringstream &iss, std::optional<std::string> first_node_token = std::nullopt);
		void parse_train_definition(std::istringstream iss);
		void log_train_journey(const train &t) const;
		bool event_happens() const;
	};

	path cast_path(algo::path journey);

	class parsing_error : public std::runtime_error
	{
	public:
		parsing_error(const std::string &what_arg);
		parsing_error(const char *what_arg);
	};
}
