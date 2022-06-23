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
	};

	Pos GetPos() const;

	bool IsAlive() const;

	void Revive();

private:
	int m_x;
	int m_y;
	bool m_alive;
};
