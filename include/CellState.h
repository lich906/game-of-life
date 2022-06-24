#pragma once
class CellState
{
public:
	CellState(int x, int y, bool alive)
		: m_x(x)
		, m_y(y)
		, m_alive(alive)
	{
	}

	struct Pos
	{
		int x;
		int y;

		bool operator!=(const Pos& other)
		{
			return other.x != x || other.y != y;
		}
	};

	Pos GetPos() const;

	bool IsAlive() const;

	CellState& Revive();

	CellState& Kill();

private:
	int m_x;
	int m_y;
	bool m_alive;
};
