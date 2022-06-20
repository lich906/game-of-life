#pragma once
#include "Constants.h"
#include "EventHandler.h"
#include "Window.h"
#include <mutex>

class DelimitersDrawer
{
public:
	DelimitersDrawer(unsigned width, unsigned height);

	bool ProcessEvent(const std::vector<EventHandler::EventData>& eventData);

	Window::DrawCallback GetDrawCallback();

private:
	static inline std::vector<sf::VertexArray> m_delimiters;
	const unsigned m_width, m_height;

	void LightUpDelimiter(bool horizontal, float position);
	static void DrawDelimiters(sf::RenderWindow& renderWindow);
	static void FadeOutDelimiters();
	static bool IsDelimiterVisible(const sf::VertexArray& delimiter);

	static void DrawCallback(sf::RenderWindow& renderWindow);
};

