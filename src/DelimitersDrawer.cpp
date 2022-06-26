#include "DelimitersDrawer.h"
#include <algorithm>

Window::DrawCallback DelimitersDrawer::GetDrawCallback()
{
	return DrawCallback;
}

void DelimitersDrawer::DrawDelimiters(sf::RenderWindow& renderWindow)
{
	for (const sf::VertexArray& delimiter : m_delimiters)
	{
		renderWindow.draw(delimiter);
	}
}

void DelimitersDrawer::FadeOutDelimiters()
{
	std::vector<sf::VertexArray> visibleDelimiters;

	for (sf::VertexArray& delimiter : m_delimiters)
	{
		if (IsDelimiterVisible(delimiter))
		{
			delimiter[0].color.r = std::max(0, delimiter[0].color.r - DELIMITERS_FADING_COEFF);
			delimiter[0].color.g = std::max(0, delimiter[0].color.g - DELIMITERS_FADING_COEFF);
			delimiter[0].color.b = std::max(0, delimiter[0].color.b - DELIMITERS_FADING_COEFF);
			delimiter[1].color.r = std::max(0, delimiter[1].color.r - DELIMITERS_FADING_COEFF);
			delimiter[1].color.g = std::max(0, delimiter[1].color.g - DELIMITERS_FADING_COEFF);
			delimiter[1].color.b = std::max(0, delimiter[1].color.b - DELIMITERS_FADING_COEFF);

			visibleDelimiters.push_back(delimiter);
		}
	}

	m_delimiters = visibleDelimiters;
}

void DelimitersDrawer::LightUpDelimiter(bool horizontal, float position)
{
	sf::VertexArray delimiter(sf::Lines, 2);
	delimiter[0].color = DELIMITER_COLOR;
	delimiter[1].color = DELIMITER_COLOR;

	if (horizontal)
	{
		delimiter[0].position = sf::Vector2f(0, position);
		delimiter[1].position = sf::Vector2f(WINDOW_WIDTH, position);
	}
	else
	{
		delimiter[0].position = sf::Vector2f(position, 0);
		delimiter[1].position = sf::Vector2f(position, WINDOW_HEIGHT);
	}

	m_delimiters.push_back(delimiter);
}

bool DelimitersDrawer::IsDelimiterVisible(const sf::VertexArray& delimiter)
{
	return delimiter[0].color.r > 0 || delimiter[0].color.g > 0 || delimiter[0].color.b > 0;
}

EventResFlag::Flag DelimitersDrawer::ProcessEvents(const std::vector<EventCollector::EventData>& eventsData)
{
	for (const EventCollector::EventData& eventData : eventsData)
	{
		switch (eventData.type)
		{
		case sf::Event::MouseMoved:
			if (eventData.event.mouseMove.x % CELL_SIZE == 0)
			{
				LightUpDelimiter(false, eventData.event.mouseMove.x);
			}
			if (eventData.event.mouseMove.y % CELL_SIZE == 0)
			{
				LightUpDelimiter(true, eventData.event.mouseMove.y);
			}
			break;
		default:
			break;
		}
	}

	return EventResFlag::Continue;
}

void DelimitersDrawer::DrawCallback(sf::RenderWindow& renderWindow)
{
	FadeOutDelimiters();
	DrawDelimiters(renderWindow);
}
