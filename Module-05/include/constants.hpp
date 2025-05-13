#pragma once
#include "common.hpp"

#include <string>

namespace consts
{
	namespace ints
	{
		inline constexpr int number_of_program_args_for_help = 2;
		inline constexpr int number_of_program_args_for_simulation = 3;
		inline constexpr int arg1 = 1;
		inline constexpr int arg2 = 2;
	}

	namespace sim
	{
		static constexpr float event_probability = 0.1f;
		static constexpr float min_railroad_length = 1.f;
		static constexpr time_unit event_duration = 5;
		static constexpr float railroad_segment_length = 1.f;
	}
	
	namespace strs
	{
		inline const std::string node_token = "Node";
		inline const std::string rail_token = "Rail";

		inline const std::string help_arg = "--help";
	
		inline const std::string error_prefix = "[ERROR] ";
		inline const std::string info_prefix = "[INFO] ";

		inline const std::string ps = ". ";  // period + space
		inline const std::string nl = "\n";
		inline const std::string psnl = ps + nl;
		inline const std::string _ = "_";

		inline const std::string result_ext = ".result";

		inline const std::string solution_not_found = "Solution was not found as the algorithm is not complete: ";
		inline const std::string readjust_inputs = "Please readjust inputs (trains, the network) to create a better setting, or try your luck with random events.";

		inline const std::string usage_string = "usage: ./trains [rails_network] [train_composition] --- launch simulation\n"
											    "              ./trains --help                              --- get help on config files\n";
		inline const std::string help_string = "rails_network:\n"
											   "-----------------------------example start-----------------------------\n"
											   "Node [node_name]\n"
											   "...\n"
											   "Rail [first_nodename] [second_nodename] [length (km)] [speed_limit (m/s)]\n"
											   "...\n"
											   "----------------------------- example end -----------------------------\n"
											   "* nodes must be declared before rails\n"
											   "* rails must refer to existing nodes\n"
											   "* a rail connects [first_nodename] to [second_nodename]\n"
											   "\n"
											   "train_composition:\n"
											   "-----------------------------example start-----------------------------\n"
											   "[train_name] [train_mass (tons)] [friction_coefficient] [acceleration_force (kilonewtons)] [brake_force (kilonewtons)] [start_node] [finish_node] [departure_time] [stop_duration]\n"
											   "...\n"
											   "----------------------------- example end -----------------------------\n"
											   "* [start_node] and [finish_node] must refer to existing nodes\n"
											   "* time is specified in the format XXhXX, with the former XX pair stands for hours, while the latter---minutes\n";
	
		inline const std::string output_dir = "output";
	}

	namespace colors
	{
		inline constexpr char const *red = "\033[31m";
		inline constexpr char const *reset = "\033[0m";
		inline constexpr char const *green = "\033[32m";
		inline constexpr char const *bright_cyan = "\033[96m";
		inline constexpr char const *bright_magenta = "\033[95m";
		inline constexpr char const *yellow = "\033[33m";
	}
}
