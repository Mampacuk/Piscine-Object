#include "logging.hpp"

namespace logging
{
	int error(const std::string &message)
	{
		std::cerr << consts::colors::red << consts::strs::error_prefix << message << consts::colors::reset << std::endl;
		return (EXIT_FAILURE);
	}

	int info(const std::string &message)
	{
		std::cout << consts::colors::yellow << consts::strs::info_prefix << message << consts::colors::reset << std::endl;
		return (EXIT_SUCCESS);
	}
}
