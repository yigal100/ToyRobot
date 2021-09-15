#include "Robot.h"

Robot::Robot(Board board): m_board(board) {}

bool Robot::Place(int x, int y, directions::Direction direction)
{
	if (m_board.CheckBounds(x, y))
	{
		m_x = x;
		m_y = y;
		m_direction = direction;
		return true;
	}
	return false;
}

void Robot::TurnLeft()
{
	m_direction = Left(m_direction);
}

void Robot::TurnRight()
{
	m_direction = Right(m_direction);
}

bool Robot::MoveForward()
{
	auto [x, y] = ToUnitVector(m_direction);
	const int newX = m_x + x;
	const int newY = m_y + y;
	if (m_board.CheckBounds(newX, newY))
	{
		m_x = newX;
		m_y = newY;
		return true;
	}
	return false;
}

std::string Robot::Report() const
{
	std::stringstream output;
	output << m_x << "," << m_y << "," << ToString(m_direction);
	return output.str();
}
