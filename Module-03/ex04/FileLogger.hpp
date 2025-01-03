#ifndef FILELOGGER_HPP
# define FILELOGGER_HPP

# include "ILogger.hpp"
# include "IHeader.hpp"

# include <fstream>
# include <stdexcept>

class FileLogger : public ILogger
{
	public:
		FileLogger(const char *filename, IHeader *header = NULL) : _header(header), _file(filename)
		{
			if (!_file.is_open())
				throw std::runtime_error("Couldn't open the file");
		}
		~FileLogger() { delete _header; }
		void write(const std::string &str)
		{
			_file << (_header ? _header->format() : "") + str << std::endl;
		}
	private:
		FileLogger(const FileLogger &other);			// deleted, as header gets deleted in dtor
		FileLogger& operator=(const FileLogger &other); // deleted, as header gets deleted in dtor
		
		IHeader *_header;
		std::ofstream _file;
};

#endif
