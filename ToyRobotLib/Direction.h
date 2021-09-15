#pragma once
#include <sstream>
#include <locale>

namespace directions
{

	enum Direction
    {
        NORTH, EAST, SOUTH, WEST
    };

	inline Direction FromString(std::string_view direction)
    {
        if (direction == "NORTH") return NORTH;
        if (direction == "EAST") return EAST;
        if (direction == "SOUTH") return SOUTH;
        if (direction == "WEST") return WEST;

        std::stringstream message;
        message << "Invalid direction: " << direction;
        throw std::invalid_argument(message.str());
    }

	inline std::string ToString(Direction direction)
    {
	    switch (direction)
	    {
        case NORTH: return "NORTH";
        case EAST: return "EAST";
        case SOUTH: return "SOUTH";
        case WEST: return "WEST";
	    }

        // unreachable
        throw std::logic_error("Invalid direction");
    }

    inline Direction Left(Direction direction)
    {
	    switch (direction)
	    {
        case NORTH: return WEST;
        case EAST: return NORTH;
        case SOUTH: return EAST;
        case WEST: return SOUTH;
	    }

        // unreachable
        throw std::logic_error("Invalid direction");
    }

    inline Direction Right(Direction direction)
    {
        switch (direction)
        {
        case NORTH: return EAST;
        case EAST: return SOUTH;
        case SOUTH: return WEST;
        case WEST: return NORTH;
        }

        // unreachable
        throw std::logic_error("Invalid direction");
    }

    inline std::pair<int,int> ToUnitVector(Direction direction) 
    {
        // (x, y) coordinates 
        switch (direction)
        {
        case NORTH: return std::make_pair(0, 1);
        case EAST: return std::make_pair(1, 0);
        case SOUTH: return std::make_pair(0, -1);
        case WEST: return std::make_pair(-1, 0);
        }

        // unreachable
        throw std::logic_error("Invalid direction");
    }

}
