#pragma once
#include <string>


class Logger
{
public:
	Logger();
	~Logger();

	static void Log(const std::string& message);
	static void Err(const std::string& message);

private:

};