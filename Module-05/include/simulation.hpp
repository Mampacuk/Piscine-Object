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
		static simulation &get();

		simulation(const simulation&) = delete;
		simulation(simulation&&) = delete;
		simulation &operator=(const simulation&) = delete;
		simulation &operator=(simulation &&) = delete;
		~simulation() = default;
		
		void run(const char *rail_network, const char *train_composition);
	private:
		simulation() = default;

		using trains = std::list<train>;
		using events = std::vector<std::unique_ptr<event>>;

		algo::dijkstra_graph _network;
		trains _trains;
		events _events;

		void initialize(const char *rail_network, const char *train_composition);
		node_ptr find_node(const std::string &name, bool throw_exception = false);
		void insert_train(train new_train);
		void insert_railroad(std::shared_ptr<railroad> new_railroad);
		void insert_node(std::shared_ptr<node> new_node);
		bool parse_node_definition(std::istringstream &iss);
		bool parse_railroad_definition(std::istringstream &iss, std::optional<std::string> first_node_token = std::nullopt);
		void parse_train_definition(std::istringstream iss);
		void log_train_journey(const train &t) const;
		bool event_happens() const;
		template <typename T, class... Args>
		std::shared_ptr<T> create_graph_object(Args&&... args)
		{
			return (std::make_shared<T>(std::forward<Args>(args)...));
		}
	};

	path cast_path(algo::path journey);

	class parsing_error : public std::runtime_error
	{
	public:
		parsing_error(const std::string &what_arg);
		parsing_error(const char *what_arg);
	};
}
