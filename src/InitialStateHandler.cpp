#include "InitialStateHandler.h"
#include <algorithm>

EventResFlag::Flag InitialStateHandler::ProcessEvents(const std::vector<EventCollector::EventData>& eventsData)
{
	for (const EventCollector::EventData& eventData : eventsData)
	{
		switch (eventData.type)
		{
		case sf::Event::EventType::MouseButtonReleased:
			if (eventData.event.mouseButton.button == sf::Mouse::Button::Left)
			{
				AddCell(eventData.event.mouseButton.x, eventData.event.mouseButton.y);
			}
			break;
		default:
			break;
		}
	}

	return EventResFlag::Continue;
}

const std::vector<CellState>& InitialStateHandler::GetInitialState() const
{
	return m_state;
}

void InitialStateHandler::ResetState()
{
	m_state.clear();
}

void InitialStateHandler::AddCell(int mouseX, int mouseY)
{
	int x = mouseX / Config::GetCellSize();
	int y = mouseY / Config::GetCellSize();

	if(!AddCellIfNecessary(x, y, true))
	{
		return;
	}

	bool leftEdge = x == 0;
	bool topEdge = y == 0;
	bool rightEdge = x == maxX;
	bool bottomEdge = y == maxY;

	if (!leftEdge)
	{
		AddCellIfNecessary(x - 1, y, false);

		if (!topEdge)
		{
			AddCellIfNecessary(x - 1, y - 1, false);
		}

		if (!bottomEdge)
		{
			AddCellIfNecessary(x - 1, y + 1, false);
		}
	}

	if (!topEdge)
	{
		AddCellIfNecessary(x, y - 1, false);

		if (!rightEdge)
		{
			AddCellIfNecessary(x + 1, y - 1, false);
		}
	}

	if (!rightEdge)
	{
		AddCellIfNecessary(x + 1, y, false);

		if (!bottomEdge)
		{
			AddCellIfNecessary(x + 1, y + 1, false);

			AddCellIfNecessary(x, y + 1, false);
		}
	}
}

bool InitialStateHandler::AddCellIfNecessary(int x, int y, bool alive)
{
	auto cell = std::find_if(m_state.begin(), m_state.end(), [x, y](const CellState& cs) {
		return cs.GetPos().x == x && cs.GetPos().y == y;
	});

	if (cell != m_state.end())
	{
		if (!cell->IsAlive() && alive)
		{
			cell->Revive();

			return true;
		}
	}
	else
	{
		m_state.push_back(CellState(x, y, alive));

		return true;
	}

	return false;
}
