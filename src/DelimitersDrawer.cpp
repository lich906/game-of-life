#include "DelimitersDrawer.h"
#include <algorithm>

DelimitersDrawer::DelimitersDrawer(unsigned width, unsigned height)
	: m_width(width)
	, m_height(height)
{
}

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
		delimiter[1].position = sf::Vector2f(m_width, position);
	}
	else
	{
		delimiter[0].position = sf::Vector2f(position, 0);
		delimiter[1].position = sf::Vector2f(position, m_height);
	}

	m_delimiters.push_back(delimiter);
}

bool DelimitersDrawer::IsDelimiterVisible(const sf::VertexArray& delimiter)
{
	return delimiter[0].color.r > 0 || delimiter[0].color.g > 0 || delimiter[0].color.b > 0;
}

bool DelimitersDrawer::ProcessEvent(const std::vector<EventHandler::EventData>& eventData)
{
	for (const EventHandler::EventData& data : eventData)
	{
		switch (data.type)
		{
		case EventHandler::EventType::LightUpVerticalDelimiter:
			LightUpDelimiter(false, data.event.mouseMove.x);
			break;
		case EventHandler::EventType::LightUpHorizontalDelimiter:
			LightUpDelimiter(true, data.event.mouseMove.y);
			break;
		case EventHandler::EventType::Closed:
			return false;
		default:
			return false;
		}
	}

	return true;
}

void DelimitersDrawer::DrawCallback(sf::RenderWindow& renderWindow)
{
	FadeOutDelimiters();
	DrawDelimiters(renderWindow);
}
