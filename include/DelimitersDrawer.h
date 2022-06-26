#pragma once
#include "Constants.h"
#include "EventCollector.h"
#include "Window.h"
#include <mutex>

class DelimitersDrawer
{
public:
	EventResFlag::Flag ProcessEvents(const std::vector<EventCollector::EventData>& eventsData);

	Window::DrawCallback GetDrawCallback();

private:
	static inline std::vector<sf::VertexArray> m_delimiters;

	void LightUpDelimiter(bool horizontal, float position);

	static void DrawDelimiters(sf::RenderWindow& renderWindow);

	static void FadeOutDelimiters();

	static bool IsDelimiterVisible(const sf::VertexArray& delimiter);

	static void DrawCallback(sf::RenderWindow& renderWindow);
};

