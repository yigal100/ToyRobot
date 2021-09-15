#include "Board.h"

Board::Board(int width, int length): m_length(length), m_width(width) {}

bool Board::CheckBounds(int x, int y) const
{ 
	return x >= 0 && x < m_width && y >= 0 && y < m_length;
}
