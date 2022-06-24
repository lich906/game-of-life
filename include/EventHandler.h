#pragma once
#include "Constants.h"
#include <vector>

class EventHandler
{
public:
	enum class EventType
	{
		None,
		LightUpVerticalDelimiter,
		LightUpHorizontalDelimiter,
		SelectCell,
		Launch,
		Closed
	};

	struct EventData
	{
		EventType type = EventType::None;
		sf::Event event;
	};

	std::vector<EventData> HandleEvents(sf::RenderWindow& window) const;
};
