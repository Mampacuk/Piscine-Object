#ifndef IHEADER_HPP
# define IHEADER_HPP

# include <string>

class IHeader
{
	public:
		virtual ~IHeader() {}
		virtual std::string format() = 0;
};

#endif
