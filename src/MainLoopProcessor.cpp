#include "MainLoopProcessor.h"

MainLoopProcessor::MainLoopProcessor(unsigned width, unsigned height, const sf::String& title)
	: m_windowWidth(width)
	, m_windowHeight(height)
	, m_window(sf::VideoMode(width, height), title)
{
}

int MainLoopProcessor::Run()
{
	while (m_window.isOpen())
	{
		if (!ProcessEvent(eventHandler.HandleEvents(m_window)))
		{
			return 0;
		}

		RenderNextFrame();
		sf::sleep(sf::milliseconds(30));
	}
}

void MainLoopProcessor::DrawDelimiters()
{
	for (const sf::VertexArray& delimiter : m_lightedUpDelimiters)
	{
		m_window.draw(delimiter);
	}
}

void MainLoopProcessor::FadeOutDelimiters()
{
	std::vector<sf::VertexArray> restDelimiters;
	std::vector<sf::VertexArray>::iterator it = m_lightedUpDelimiters.begin();
	for (; it != m_lightedUpDelimiters.end(); ++it)
	{
		sf::Uint8 nextAlpha = std::max(0, (*it)[0].color.a - fadingCoeff);
		(*it)[0].color.a = nextAlpha;
		(*it)[1].color.a = nextAlpha;

		if (nextAlpha != 0)
		{
			restDelimiters.push_back(*it);
		}
	}

	m_lightedUpDelimiters = restDelimiters;
}

void MainLoopProcessor::LightUpDelimiter(bool horizontal, float position)
{
	sf::VertexArray delimiter(sf::Lines, 2);
	delimiter[0].color = sf::Color(delimiterColor);
	delimiter[1].color = sf::Color(delimiterColor);

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

	m_lightedUpDelimiters.push_back(delimiter);
}

bool MainLoopProcessor::ProcessEvent(const std::vector<EventHandler::EventData>& eventData)
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

void MainLoopProcessor::RenderNextFrame()
{
	m_window.clear();
	FadeOutDelimiters();
	DrawDelimiters();

	m_window.display();
}
