#include "algorithm.hpp"
#include "constants.hpp"
#include "logging.hpp"
#include "simulation.hpp"

int main(int argc, char **argv)
{
	if (argc == consts::ints::number_of_program_args_for_help && std::string(argv[consts::ints::arg1]) == consts::strs::help_arg)
	{
		return (logging::info(consts::strs::help_string));
	}
	else if (argc == consts::ints::number_of_program_args_for_simulation)
	{
		try
		{
			sim::simulation trains(argv[consts::ints::arg1], argv[consts::ints::arg2]);
			trains.run();
		}
		catch (const algo::algorithmic_error &e)
		{
			return (logging::error(consts::strs::solution_not_found + e.what() + consts::strs::psnl + consts::strs::readjust_inputs));
		}
		catch (const std::exception &e)
		{
			return (logging::error(e.what()));
		}
	}
	else
	{
		return (logging::info(consts::strs::usage_string));
	}
}
