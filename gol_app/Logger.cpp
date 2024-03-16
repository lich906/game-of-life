#include <iomanip>
#include "Logger.h"

constexpr auto DateTimeFormat = "%F %T %z";

void Logger::Log(const std::string& msg)
{
	m_stream << '[' << GetCurrentDateTimeAsString() << "] " << msg << std::endl;
}

void Logger::LogEvent(
	const std::string& layerName,
	const core::event::Event& event)
{
	m_stream << "Layer=" << layerName << " | " << event.ToString() << ':' << std::endl;
	m_stream << "\t#additional info.\n";
}

std::string Logger::GetCurrentDateTimeAsString() const
{
	auto t = std::time(nullptr);
#pragma warning(disable : 4996)
	auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, DateTimeFormat);
	return oss.str();
}
