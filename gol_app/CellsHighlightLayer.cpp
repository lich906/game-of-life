#include <format>

#include "CellsHighlightLayer.h"
#include "core/event/EventDispatcher.h"

#define BIND_EVENT_FN(x) std::bind(&CellsHighlightLayer::x, this, std::placeholders::_1)

using namespace core;

void CellsHighlightLayer::OnEvent(event::Event& event)
{
	event::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<event::MouseMovedEvent>(BIND_EVENT_FN(HandleMouseMovement));
	dispatcher.Dispatch<event::MouseLeaveEvent>(BIND_EVENT_FN(HandleMouseLeave));
}

bool CellsHighlightLayer::HandleMouseMovement(event::MouseMovedEvent& event)
{
	float mouseX = event.GetX();
	float mouseY = event.GetY();
	int cellSize = m_conf.GetCellSize();

	int x = (int)(mouseX / cellSize);
	int y = (int)(mouseY / cellSize);

	if (!m_hoveredCell)
	{
		UpdateHoveredCell(x, y, cellSize);
	}
	else if (!IsHoveredCell(x, y))
	{
		// place previous hovered cell to fading queue
		UpdateHoveredCell(x, y, cellSize);
	}

	return true; // stop event propagation
}

bool CellsHighlightLayer::HandleMouseLeave(event::MouseLeaveEvent& event)
{
	m_hoveredCell = std::nullopt;
	m_logger.Log(std::format("Mouse left the window, cell hover removed.\n"));
	return true; // stop event propagation
}

void CellsHighlightLayer::UpdateHoveredCell(int x, int y, int cellSize)
{
	m_hoveredCell = HoveredCell{
		x, y,
		CalcBoundingRect(x, y, cellSize)
	};

	m_logger.Log(
		std::format("New hovered cell:\tx={} y={} left={} right={} top={} bottom={}\n",
			m_hoveredCell->x,
			m_hoveredCell->y,
			m_hoveredCell->boundingRect.left,
			m_hoveredCell->boundingRect.right,
			m_hoveredCell->boundingRect.top,
			m_hoveredCell->boundingRect.bottom)
	);
}

CellsHighlightLayer::BoundingRect CellsHighlightLayer::CalcBoundingRect(int x, int y, int cellSize) const
{
	return BoundingRect{
		int(x * cellSize),
		int((x + 1) * cellSize),
		int(y * cellSize),
		int((y + 1) * cellSize)
	};
}

bool CellsHighlightLayer::IsHoveredCell(int x, int y)
{
	return m_hoveredCell->x == x && m_hoveredCell->y == y;
}
