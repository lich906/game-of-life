#pragma once
#include "Constants.h"
#include "EventHandler.h"
#include <queue>

class DelimitersDrawProcessor
{
public:
	DelimitersDrawProcessor(unsigned width, unsigned height, const sf::String& title);

	int Run();

private:
	const unsigned m_windowWidth, m_windowHeight;

	void DrawDelimiters();
	void FadeOutDelimiters();
	void LightUpDelimiter(bool horizontal, float position);
	bool IsDelimiterVisible(const sf::VertexArray& delimiter) const;

	bool ProcessEvent(const std::vector<EventHandler::EventData>& eventData);
	
	void RenderNextFrame();

	EventHandler eventHandler;

	std::vector<sf::VertexArray> m_delimiters;

	sf::RenderWindow m_window;
};

