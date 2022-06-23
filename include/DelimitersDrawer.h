#pragma once
#include "Constants.h"
#include "EventHandler.h"
#include "Window.h"
#include <mutex>

class DelimitersDrawer
{
public:
	bool ProcessEvents(const std::vector<EventHandler::EventData>& eventsData);

	Window::DrawCallback GetDrawCallback();

private:
	static inline std::vector<sf::VertexArray> m_delimiters;

	void LightUpDelimiter(bool horizontal, float position);

	static void DrawDelimiters(sf::RenderWindow& renderWindow);

	static void FadeOutDelimiters();

	static bool IsDelimiterVisible(const sf::VertexArray& delimiter);

	static void DrawCallback(sf::RenderWindow& renderWindow);
};

