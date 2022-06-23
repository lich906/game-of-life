#pragma once
#include "EventHandler.h"
#include "CellState.h"
#include <vector>

class InitialStateHandler
{
public:
	bool ProcessEvents(const std::vector<EventHandler::EventData>& eventsData);

	const std::vector<CellState>& GetInitialState();

private:
	const int maxX = WINDOW_WIDTH / CELL_SIZE;
	const int maxY = WINDOW_HEIGHT / CELL_SIZE;

	/*
	Params:
	int x -- mouse click x coordinate
	int y -- mouse click y coordinate
	*/
	void AddCell(int x, int y);

	/*
	If cell state with coords (x, y) does not exists -- create cell at (x, y) with 'alive' arg state
	Otherwise
	  If cell is dead -- revive the cell
	  Otherwise -- do nothing
	
	Returns:
	true -- if cell was added or revived
	false -- otherwise
	*/
	bool AddCellIfNecessary(int x, int y, bool alive);

	std::vector<CellState> m_state;
};
