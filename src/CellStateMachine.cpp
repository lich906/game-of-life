#include "CellStateMachine.h"
#include <algorithm>

CellStateMachine::CellStateMachine(int maxX, int maxY)
	: maxX(maxX)
	, maxY(maxY)
{
}

void CellStateMachine::SetInitialState(const std::vector<CellState>& initialState)
{
	m_state = initialState;
}

void CellStateMachine::NextState()
{
	m_bufferState.clear();
	size_t adjacentLiveCells;

	for (const CellState& cellState : m_state)
	{
		auto cellPos = cellState.GetPos();
		adjacentLiveCells = CountAdjacentLiveCells(cellPos);

		
		if (cellState.IsAlive())
		{
			if (adjacentLiveCells < 2 || adjacentLiveCells > 3)
			{
				m_bufferState.push_back(CellState(cellState).Kill());
			}
			else
			{
				m_bufferState.push_back(cellState);
			}
		}
		else if (adjacentLiveCells == 3)
		{
			m_bufferState.push_back(CellState(cellState).Revive());
			AddAdjacentDeadCellsToBuffer(cellPos);
		}
		else
		{
			m_bufferState.push_back(cellState);
		}
	}

	std::swap(m_state, m_bufferState);
}

const std::vector<CellState>& CellStateMachine::GetState() const
{
	return m_state;
}

size_t CellStateMachine::CountAdjacentLiveCells(const CellState::Pos& cellPos)
{
	return std::count_if(m_state.begin(), m_state.end(), [&cellPos](const CellState& cs) {
		return 
			cs.IsAlive() && 
			cs.GetPos() != cellPos && 
			abs(cs.GetPos().x - cellPos.x) < 2 && 
			abs(cs.GetPos().y - cellPos.y) < 2;
	});
}

void CellStateMachine::PushToBufferIfNotExists(const CellState& cell)
{
	if (std::find_if(m_state.begin(), m_state.end(), [&cell](const CellState& cs) {
		return cs.GetPos() == cell.GetPos();
	}) == m_state.end() && 
	std::find_if(m_bufferState.begin(), m_bufferState.end(), [&cell](const CellState& cs) {
		return cs.GetPos() == cell.GetPos();
	}) == m_bufferState.end())
	{
		m_bufferState.push_back(cell);
	}
}

void CellStateMachine::AddAdjacentDeadCellsToBuffer(const CellState::Pos& cellPos)
{
	bool leftEdge = cellPos.x == 0;
	bool rightEdge = cellPos.x == maxX;
	bool topEdge = cellPos.y == 0;
	bool bottomEdge = cellPos.x == maxY;

	if (!leftEdge)
	{
		PushToBufferIfNotExists(CellState(cellPos.x - 1, cellPos.y, false));

		if (!topEdge)
		{
			PushToBufferIfNotExists(CellState(cellPos.x - 1, cellPos.y - 1, false));
		}

		if (!bottomEdge)
		{
			PushToBufferIfNotExists(CellState(cellPos.x - 1, cellPos.y + 1, false));
		}
	}

	if (!topEdge)
	{
		PushToBufferIfNotExists(CellState(cellPos.x, cellPos.y - 1, false));
	}

	if (!bottomEdge)
	{
		PushToBufferIfNotExists(CellState(cellPos.x, cellPos.y + 1, false));
	}

	if (!rightEdge)
	{
		PushToBufferIfNotExists(CellState(cellPos.x + 1, cellPos.y, false));

		if (!topEdge)
		{
			PushToBufferIfNotExists(CellState(cellPos.x + 1, cellPos.y - 1, false));
		}

		if (!bottomEdge)
		{
			PushToBufferIfNotExists(CellState(cellPos.x + 1, cellPos.y + 1, false));
		}
	}

}
