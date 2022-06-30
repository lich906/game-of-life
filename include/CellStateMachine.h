#pragma once
#include "CellState.h"
#include <vector>

class CellStateMachine
{
public:
	CellStateMachine(int maxX, int maxY);

	void SetInitialState(const std::vector<CellState>& initialState);

	void NextState();

	const std::vector<CellState>& GetState() const;

private:
	const int maxX, maxY;

	size_t CountAdjacentLiveCells(const std::vector<CellState>& state, const CellState::Pos& cellPos) const;

	void PushToBufferIfNotExists(const CellState& cell);

	void AddAdjacentDeadCellsToBuffer(const CellState::Pos& cell);

	bool CellAtPosExists(const std::vector<CellState>& state, const CellState::Pos& pos) const;

	void RemoveRedundantDeadCells(std::vector<CellState>& state);

	std::vector<CellState> m_state;

	std::vector<CellState> m_bufferState;
};
