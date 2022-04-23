#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

constexpr unsigned delimitersInterval = 10;

class EventHandler
{
public:
	enum class EventType
	{
		None,
		LightUpVerticalDelimiter,
		LightUpHorizontalDelimiter,
		Closed
	};

	struct EventData
	{
		EventType type = EventType::None;
		sf::Event event;
	};

	std::vector<EventData> HandleEvents(sf::RenderWindow& window);
};

