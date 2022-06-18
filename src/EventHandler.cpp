#include "EventHandler.h"

std::vector<EventHandler::EventData> EventHandler::HandleEvents(sf::RenderWindow& window) const
{
	std::vector<EventData> eventData;
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseMoved:
			if (event.mouseMove.x % delimitersInterval == 0)
			{
				eventData.push_back({ EventType::LightUpVerticalDelimiter, event });
			}
			if (event.mouseMove.y % delimitersInterval == 0)
			{
				eventData.push_back({ EventType::LightUpHorizontalDelimiter, event });
			}
			break;
		case sf::Event::Closed:
			eventData.push_back({ EventType::Closed });
		default:
			break;
		}
	}

	return eventData;
}
