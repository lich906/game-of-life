#pragma once
#include "EventCollector.h"
#include "Constants.h"

class CommonEventProcessor
{
public:
	static EventResFlag::Flag ProcessEvents(const std::vector<EventCollector::EventData>& eventsData);
};
