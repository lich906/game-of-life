#include "InitialStateHandler.h"
#include <algorithm>

InitialStateHandler::EventProcessingResult InitialStateHandler::ProcessEvents(const std::vector<EventHandler::EventData>& eventsData)
{
	for (const EventHandler::EventData& data : eventsData)
	{
		switch (data.type)
		{
		case EventHandler::EventType::SelectCell:
			if (data.event.mouseButton.button == sf::Mouse::Button::Left)
			{
				AddCell(data.event.mouseButton.x, data.event.mouseButton.y);
			}
			break;
		case EventHandler::EventType::Closed:
			return EventProcessingResult::Exit;
		case EventHandler::EventType::Launch:
			return EventProcessingResult::Launch;
		default:
			break;
		}
	}

	return EventProcessingResult::Continue;
}

const std::vector<CellState>& InitialStateHandler::GetInitialState()
{
	return m_state;
}

void InitialStateHandler::AddCell(int mouseX, int mouseY)
{
	int x = mouseX / CELL_SIZE;
	int y = mouseY / CELL_SIZE;

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
