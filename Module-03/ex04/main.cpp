#include "ConstantHeader.hpp"
#include "DateHeader.hpp"
#include "FileLogger.hpp"
#include "StreamLogger.hpp"

#include <vector>
#include <iostream>

// the Dependency-Inversion Principle (DIP) states that:
// a. High-level modules should not depend on low-level modules. Both should depend on abstractions.
// *** a high-level module (an ILogger implementation) should not depend on low-level modules (ConstantHeader, DateHeader).
// *** both should depend on abstractions (i.e. both high-level ILogger and low-level header classes depend on
// *** IHeader abstraction)
// b. Abstractions should not depend on details. Details should depend on abstractions.
// *** none of interface classes (ILogger, IHeader) depend on their implementations. their implementations
// *** directly depend on them instead.
int main()
{
	std::vector<ILogger*> loggers;
	
	loggers.push_back(new FileLogger("log1.txt"));									// file logger, no header
	loggers.push_back(new FileLogger("log2.txt", new DateHeader));					// file logger, date header
	loggers.push_back(new FileLogger("log3.txt", new ConstantHeader("[blabla] ")));	// file logger, constant header
	loggers.push_back(new StreamLogger(std::cout));									// stream logger, no header
	loggers.push_back(new StreamLogger(std::cout, new DateHeader));					// stream logger, date header
	loggers.push_back(new StreamLogger(std::cout, new ConstantHeader("[blabla] ")));// stream logger, constant header

	for (unsigned int i = 0; i < loggers.size(); i++)
		loggers[i]->write("Dependency Inversion");
}
