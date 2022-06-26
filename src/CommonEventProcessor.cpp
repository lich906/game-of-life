#include "CommonEventProcessor.h"

EventResFlag::Flag CommonEventProcessor::ProcessEvents(const std::vector<EventCollector::EventData>& eventsData)
{
	for (const EventCollector::EventData& eventData : eventsData)
	{
		switch (eventData.type)
		{
		case sf::Event::EventType::Closed:
			return EventResFlag::Exit;
		case sf::Event::EventType::KeyReleased:
			if (eventData.event.key.code == sf::Keyboard::Backspace)
			{
				return EventResFlag::ResetGame;
			}
			if (eventData.event.key.code == sf::Keyboard::Enter)
			{
				return EventResFlag::LaunchGame;
			}
			break;
		default:
			break;
		}
	}

	return EventResFlag::Continue;
}
