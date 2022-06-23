#include "CellState.h"

CellState::Pos CellState::GetPos() const
{
	return { m_x, m_y };
}

bool CellState::IsAlive() const
{
	return m_alive;
}

void CellState::Revive()
{
	m_alive = true;
}
