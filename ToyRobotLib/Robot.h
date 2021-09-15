#pragma once
#include "Board.h"
#include "Direction.h"

class Robot
{
public:
    Robot(Board board);

    bool Place(int x, int y, directions::Direction direction);
    void TurnLeft();
    void TurnRight();
    bool MoveForward();
    [[nodiscard]] std::string Report() const;

private:
    Board m_board;
    int m_x = 0, m_y = 0;
    directions::Direction m_direction = directions::NORTH;
};
