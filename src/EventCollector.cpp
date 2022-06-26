#include "EventCollector.h"

std::vector<EventCollector::EventData> EventCollector::CollectEvents(sf::RenderWindow& window)
{
	std::vector<EventData> eventData;
	sf::Event event;
	while (window.pollEvent(event))
	{
		eventData.push_back({ event.type, event });
	}

	return eventData;
}
