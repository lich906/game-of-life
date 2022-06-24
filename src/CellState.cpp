#include "CellState.h"

CellState::Pos CellState::GetPos() const
{
	return { m_x, m_y };
}

bool CellState::IsAlive() const
{
	return m_alive;
}

CellState& CellState::Revive()
{
	m_alive = true;

	return *this;
}

CellState& CellState::Kill()
{
	m_alive = false;

	return *this;
}
