#include "Logger.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

std::vector<LogEntry> Logger::messages;

Logger::Logger() {}

Logger::~Logger() {}

std::string currentDateTime()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm timeinfo;
	localtime_s(&timeinfo, &now);

	char buffer[30];
	std::strftime(buffer, sizeof(buffer), "%d-%b-%Y %M:%S", &timeinfo);

	return std::string(buffer);
}

void Logger::Log(const std::string& message)
{
	LogEntry logEntry;
	logEntry.type = LOG_INFO;
	
	logEntry.message = "LOG: [" + currentDateTime() + "]: " + message;
	std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;

	messages.push_back(logEntry);
}

void Logger::Err(const std::string& message)
{

	LogEntry logEntry;
	logEntry.type = LOG_ERROR;

	logEntry.message = "ERR: [" + currentDateTime() + "]: " + message;
	std::cout << "\x1B[91m" << logEntry.message << "\033[0m" << std::endl;

	messages.push_back(logEntry);
}