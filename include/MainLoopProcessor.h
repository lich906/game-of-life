#pragma once
#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include <queue>

constexpr uint32_t delimiterColor = 0xF0F8FF44;
constexpr sf::Uint8 fadingCoeff = 8;
const sf::Time delayTime = sf::milliseconds(30);

class MainLoopProcessor
{
public:
	MainLoopProcessor(unsigned width, unsigned height, const sf::String& title);

	int Run();

private:
	const unsigned m_windowWidth, m_windowHeight;

	void DrawDelimiters();
	void FadeOutDelimiters();
	void LightUpDelimiter(bool horizontal, float position);
	std::vector<sf::VertexArray> m_lightedUpDelimiters;

	bool ProcessEvent(const std::vector<EventHandler::EventData>& eventData);
	EventHandler eventHandler;

	void RenderNextFrame();

	sf::RenderWindow m_window;
};

