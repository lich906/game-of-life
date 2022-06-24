#pragma once
#include "CellState.h"
#include <vector>

class CellStateMachine
{
public:
	void SetInitialState(const std::vector<CellState>& initialState);

	void NextState();

	const std::vector<CellState>& GetState();

private:
	size_t CountAdjacentLiveCells(const CellState::Pos& cellPos);

	std::vector<CellState> m_state;

	std::vector<CellState> m_bufferState;
};
