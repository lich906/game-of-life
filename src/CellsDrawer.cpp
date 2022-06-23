#include "CellsDrawer.h"

Window::DrawCallback CellsDrawer::GetDrawCallback()
{
	return DrawCallback;
}

void CellsDrawer::AttachCellsState(const std::vector<CellState>& state)
{
	m_attachedState = std::addressof(state);
}

void CellsDrawer::DrawCallback(sf::RenderWindow& renderWindow)
{
	for (const CellState& cellState : *m_attachedState)
	{
		DrawCell(renderWindow, cellState);
	}
}

void CellsDrawer::DrawCell(sf::RenderWindow& renderWindow, const CellState& cellState)
{
	auto cellPos = cellState.GetPos();

	int leftTopX = cellPos.x * CELL_SIZE + 1;
	int leftTopY = cellPos.y * CELL_SIZE + 1;

	sf::ConvexShape cell(4);

	cell.setPoint(0, sf::Vector2f(leftTopX, leftTopY));
	cell.setPoint(1, sf::Vector2f(leftTopX + CELL_SIZE - 2, leftTopY));
	cell.setPoint(2, sf::Vector2f(leftTopX + CELL_SIZE - 2, leftTopY + CELL_SIZE - 2));
	cell.setPoint(3, sf::Vector2f(leftTopX, leftTopY + CELL_SIZE - 2));

	cell.setFillColor(cellState.IsAlive() ? LIVE_CELL_COLOR : DEAD_CELL_COLOR);

	renderWindow.draw(cell);
}
