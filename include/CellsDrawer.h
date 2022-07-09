#pragma once
#include "Window.h"
#include "CellState.h"
#include "Config.h"
#include "IDrawer.h"

class CellsDrawer : public IDrawer
{
public:
	Window::DrawCallback GetDrawCallback() const override;

	static void AttachCellsState(const std::vector<CellState>& state);

private:
	static void DrawCallback(sf::RenderWindow& renderWindow);

	static void DrawCell(sf::RenderWindow& renderWindow, const CellState& cellState);

	static inline const std::vector<CellState>* m_attachedState;
};
