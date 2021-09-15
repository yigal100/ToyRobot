#pragma once

class Board
{
public:
	explicit Board(int width = 5, int length = 5);
	[[nodiscard]] bool CheckBounds(int x, int y) const;
	[[nodiscard]] int Length() const { return m_length; }
	[[nodiscard]] int Width() const { return m_width; }

private:
    const int m_length;
    const int m_width;
};
