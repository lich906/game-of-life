#include "CellStateMachine.h"
#include <algorithm>

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
		adjacentLiveCells = CountAdjacentLiveCells(cellState.GetPos());

		if (adjacentLiveCells)
		{
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
			else if (adjacentLiveCells > 2)
			{
				m_bufferState.push_back(CellState(cellState).Revive());
			}
			else
			{
				m_bufferState.push_back(cellState);
			}
		}
	}

	std::swap(m_state, m_bufferState);
}

const std::vector<CellState>& CellStateMachine::GetState()
{
	return m_state;
}

size_t CellStateMachine::CountAdjacentLiveCells(const CellState::Pos& cellPos)
{
	return std::count_if(m_state.begin(), m_state.end(), [&cellPos](const CellState& cs) {
		return 
			cs.GetPos() != cellPos &&
			cs.IsAlive() && 
			abs(cs.GetPos().x - cellPos.x) < 2 && 
			abs(cs.GetPos().y - cellPos.y) < 2;
	});
}
