#ifndef DATEHEADER_HPP
# define DATEHEADER_HPP

# include <ctime>

# include "IHeader.hpp"

class DateHeader : public IHeader
{
	public:
		DateHeader() {}
		DateHeader(const DateHeader&) {}
		DateHeader &operator=(const DateHeader&) { return (*this); }
		~DateHeader() {}
		std::string format()
		{
			time_t now = time(NULL);
			const std::string timestamp = ctime(&now); // has weird newline at the end
			return "[" + timestamp.substr(0, timestamp.size() - 1) + "] ";
		}
};

#endif
