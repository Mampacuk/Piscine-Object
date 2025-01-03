#ifndef CONSTANTHEADER_HPP
# define CONSTANTHEADER_HPP

# include "IHeader.hpp"

class ConstantHeader : public IHeader
{
	public:
		ConstantHeader() : _header() {}
		ConstantHeader(const std::string &header) : _header(header) {}
		ConstantHeader(const ConstantHeader &other) : _header(other._header) {}
		ConstantHeader &operator=(const ConstantHeader &other) { _header = other._header; return (*this); }
		~ConstantHeader() {}
		std::string format()
		{
			return (_header);
		}
	private:
		std::string _header;
};

#endif
