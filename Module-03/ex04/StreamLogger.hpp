#ifndef STREAMLOGGER_HPP
# define STREAMLOGGER_HPP

# include "ILogger.hpp"
# include "IHeader.hpp"

# include <fstream>
# include <stdexcept>

class StreamLogger : public ILogger
{
	public:
		StreamLogger(std::ostream &stream, IHeader *header = NULL) : _header(header), _stream(stream) {}
		~StreamLogger() {}
		void write(const std::string &str)
		{
			_stream << (_header ? _header->format() : "") + str << std::endl;
		}
	private:
		StreamLogger(const StreamLogger &other);			// deleted, as const members
		StreamLogger& operator=(const StreamLogger &other); // deleted, as const members

		IHeader *_header;
		std::ostream &_stream;
};

#endif
