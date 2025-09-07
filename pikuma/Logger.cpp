#include "Logger.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

Logger::Logger() {}

Logger::~Logger() {}

std::string currentDateTime()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm timeinfo;
	localtime_s(&timeinfo, &now);

	char buffer[30];
	std::strftime(buffer, sizeof(buffer), "%d-%b-%Y:%M:%S", &timeinfo);

	return std::string(buffer);
}

void Logger::Log(const std::string& message)
{
	std::string output = "LOG: [" + currentDateTime() + "]: " + message;
	std::cout << "\x1B[32m" << output << "\033[0m" << std::endl;
}

void Logger::Err(const std::string& message)
{
	std::string output = "ERR: [" + currentDateTime() + "]: " + message;
	std::cout << "\x1B[91m" << output << "\033[0m" << std::endl;
}