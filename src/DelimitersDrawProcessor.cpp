#include "DelimitersDrawProcessor.h"
#include<algorithm>

DelimitersDrawProcessor::DelimitersDrawProcessor(unsigned width, unsigned height, const sf::String& title)
	: m_windowWidth(width)
	, m_windowHeight(height)
	, m_window(sf::VideoMode(width, height), title)
{
}

int DelimitersDrawProcessor::Run()
{
	sf::Clock clock;
	while (m_window.isOpen())
	{
		if (!ProcessEvent(eventHandler.HandleEvents(m_window)))
		{
			return 0;
		}

		if (clock.getElapsedTime() > sf::milliseconds(20))
		{
			RenderNextFrame();
			clock.restart();
		}
	}
}

void DelimitersDrawProcessor::DrawDelimiters()
{
	for (const sf::VertexArray& delimiter : m_delimiters)
	{
		m_window.draw(delimiter);
	}
}

void DelimitersDrawProcessor::FadeOutDelimiters()
{
	std::vector<sf::VertexArray> visibleDelimiters;

	for (sf::VertexArray delimiter : m_delimiters)
	{
		if (IsDelimiterVisible(delimiter))
		{
			delimiter[0].color.r = std::max(0, delimiter[0].color.r - fadingCoeff);
			delimiter[0].color.g = std::max(0, delimiter[0].color.g - fadingCoeff);
			delimiter[0].color.b = std::max(0, delimiter[0].color.b - fadingCoeff);
			delimiter[1].color.r = std::max(0, delimiter[1].color.r - fadingCoeff);
			delimiter[1].color.g = std::max(0, delimiter[1].color.g - fadingCoeff);
			delimiter[1].color.b = std::max(0, delimiter[1].color.b - fadingCoeff);

			visibleDelimiters.push_back(delimiter);
		}
	}

	m_delimiters = visibleDelimiters;
}

void DelimitersDrawProcessor::LightUpDelimiter(bool horizontal, float position)
{
	sf::VertexArray delimiter(sf::Lines, 2);
	delimiter[0].color = delimiterColor;
	delimiter[1].color = delimiterColor;

	if (horizontal)
	{
		delimiter[0].position = sf::Vector2f(0, position);
		delimiter[1].position = sf::Vector2f(m_windowWidth, position);
	}
	else
	{
		delimiter[0].position = sf::Vector2f(position, 0);
		delimiter[1].position = sf::Vector2f(position, m_windowHeight);
	}

	m_delimiters.push_back(delimiter);
}

bool DelimitersDrawProcessor::IsDelimiterVisible(const sf::VertexArray& delimiter) const
{
	return delimiter[0].color.r || delimiter[0].color.g || delimiter[0].color.b;
}

bool DelimitersDrawProcessor::ProcessEvent(const std::vector<EventHandler::EventData>& eventData)
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

void DelimitersDrawProcessor::RenderNextFrame()
{
	FadeOutDelimiters();
	DrawDelimiters();

	m_window.display();
}
