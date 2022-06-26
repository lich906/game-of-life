#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace EventResFlag
{
using Flag = uint8_t;

constexpr Flag Continue = 0b00000001;

constexpr Flag LaunchGame = 0b00000010;

constexpr Flag Exit = 0b00000100;

constexpr Flag ResetGame = 0b00001000;
}

class EventCollector
{
public:
	struct EventData
	{
		sf::Event::EventType type = sf::Event::EventType::MouseEntered;
		sf::Event event;
	};

	static std::vector<EventData> CollectEvents(sf::RenderWindow& window);
};
