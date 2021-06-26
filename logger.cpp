#include <fstream>
#include "logger.h"

std::ofstream file;

void logger_init()
{
	file.open("log.txt", std::ofstream::out);
}

void logger_write(const char* message)
{
	file << message << std::endl;
}

