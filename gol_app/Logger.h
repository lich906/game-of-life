#pragma once

#include <string>

#include "core/core.h"

class Logger
{
public:
	void Log(const std::string& msg);

	void LogEvent(
		const std::string& layerName,
		const core::event::Event& event
	);

private:
	std::string GetCurrentDateTimeAsString() const;

	std::ostream& m_stream = std::cout;
};
