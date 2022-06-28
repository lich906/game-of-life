#pragma once
#include "Window.h"
#include "CellState.h"
#include "Config.h"

class CellsDrawer
{
public:
	static Window::DrawCallback GetDrawCallback();

	static void AttachCellsState(const std::vector<CellState>& state);

private:
	static void DrawCallback(sf::RenderWindow& renderWindow);

	static void DrawCell(sf::RenderWindow& renderWindow, const CellState& cellState);

	static inline const std::vector<CellState>* m_attachedState;
};
