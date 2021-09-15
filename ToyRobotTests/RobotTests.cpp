#include "Robot.h"
#include "boost/ut.hpp"

using namespace boost::ut;
using namespace bdd;
using namespace std::literals::string_literals;

suite RobotTests = [] {
    feature("Robot") = [] {
        scenario("Clockwise movement") = [] {
            given("Robot is placed at (3,3) facing NORTH") = [] {
                const Board board;
                Robot toyRobot{ board };
                expect(that % toyRobot.Place(3, 3, directions::NORTH) >> fatal);
                expect(that % "3,3,NORTH"s == toyRobot.Report());

                when("Robot turns right") = [&]() {
                    toyRobot.TurnRight();
                    then("Robot is at (3,3) facing EAST") = [&] {
                        expect(that % "3,3,EAST"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that % toyRobot.MoveForward());
                    then("Robot is at (4,3) facing EAST") = [&] {
                        expect(that % "4,3,EAST"s == toyRobot.Report());
                    };
                };
                when("Robot turns right") = [&]() {
                    toyRobot.TurnRight();
                    then("Robot is at (4,3) facing SOUTH") = [&] {
                        expect(that % "4,3,SOUTH"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that% toyRobot.MoveForward());
                    then("Robot is at (4,2) facing SOUTH") = [&] {
                        expect(that % "4,2,SOUTH"s == toyRobot.Report());
                    };
                };
                when("Robot turns right") = [&]() {
                    toyRobot.TurnRight();
                    then("Robot is at (4,2) facing WEST") = [&] {
                        expect(that % "4,2,WEST"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that% toyRobot.MoveForward());
                    then("Robot is at (3,2) facing WEST") = [&] {
                        expect(that % "3,2,WEST"s == toyRobot.Report());
                    };
                };
            	when("Robot turns right") = [&]() {
                    toyRobot.TurnRight();
                    then("Robot is at (3,2) facing NORTH") = [&] {
                        expect(that % "3,2,NORTH"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that % toyRobot.MoveForward());
                    then("Robot is at (3,3) facing NORTH") = [&] {
                        expect(that % "3,3,NORTH"s == toyRobot.Report());
                    };
                };
            };
        };

        scenario("Counter-clockwise movement") = [] {
            given("Robot is placed at (3,3) facing NORTH") = [] {
                const Board board;
                Robot toyRobot{ board };
                expect(that% toyRobot.Place(3, 3, directions::NORTH) >> fatal);
                expect(that % "3,3,NORTH"s == toyRobot.Report());

                when("Robot turns left") = [&]() {
                    toyRobot.TurnLeft();
                    then("Robot is at (3,3) facing WEST") = [&] {
                        expect(that % "3,3,WEST"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that % toyRobot.MoveForward());
                    then("Robot is at (2,3) facing WEST") = [&] {
                        expect(that % "2,3,WEST"s == toyRobot.Report());
                    };
                };
                when("Robot turns left") = [&]() {
                    toyRobot.TurnLeft();
                    then("Robot is at (2,3) facing SOUTH") = [&] {
                        expect(that % "2,3,SOUTH"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that % toyRobot.MoveForward());
                    then("Robot is at (2,2) facing SOUTH") = [&] {
                        expect(that % "2,2,SOUTH"s == toyRobot.Report());
                    };
                };
                when("Robot turns left") = [&]() {
                    toyRobot.TurnLeft();
                    then("Robot is at (2,2) facing EAST") = [&] {
                        expect(that % "2,2,EAST"s == toyRobot.Report());
                    };
                };
            	when("Robot moves forward") = [&]() {
                    expect(that % toyRobot.MoveForward());
                    then("Robot is at (3,2) facing EAST") = [&] {
                        expect(that % "3,2,EAST"s == toyRobot.Report());
                    };
                };

                when("Robot turns left") = [&]() {
                    toyRobot.TurnLeft();
                    then("Robot faces NORTH") = [&] {
                        expect(that % "3,2,NORTH"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that % toyRobot.MoveForward());
                    then("Robot is at (3,3) facing NORTH") = [&] {
                        expect(that % "3,3,NORTH"s == toyRobot.Report());
                    };
                };
            };
        };

        scenario("Verify robot doesn't fall off the edge") = [] {
            given("Robot is placed at origin on a 1x1 board facing NORTH") = [] {
                const Board board(1,1);
                Robot toyRobot{ board };
                expect(that % "0,0,NORTH"s == toyRobot.Report());

                when("Robot turns left") = [&]() {
                    toyRobot.TurnLeft();
                    then("Robot is at (0,0) facing WEST") = [&] {
                        expect(that % "0,0,WEST"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that % !toyRobot.MoveForward());
                    then("Robot is at (0,0) facing WEST") = [&] {
                        expect(that % "0,0,WEST"s == toyRobot.Report());
                    };
                };
                when("Robot turns left") = [&]() {
                    toyRobot.TurnLeft();
                    then("Robot is at (0,0) facing SOUTH") = [&] {
                        expect(that % "0,0,SOUTH"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that % !toyRobot.MoveForward());
                    then("Robot is at (0,0) facing SOUTH") = [&] {
                        expect(that % "0,0,SOUTH"s == toyRobot.Report());
                    };
                };
                when("Robot turns left") = [&]() {
                    toyRobot.TurnLeft();
                    then("Robot is at (0,0) facing EAST") = [&] {
                        expect(that % "0,0,EAST"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that % !toyRobot.MoveForward());
                    then("Robot is at (0,0) facing EAST") = [&] {
                        expect(that % "0,0,EAST"s == toyRobot.Report());
                    };
                };

                when("Robot turns left") = [&]() {
                    toyRobot.TurnLeft();
                    then("Robot is at (0,0) facing NORTH") = [&] {
                        expect(that % "0,0,NORTH"s == toyRobot.Report());
                    };
                };
                when("Robot moves forward") = [&]() {
                    expect(that % !toyRobot.MoveForward());
                    then("Robot is at (0,0) facing NORTH") = [&] {
                        expect(that % "0,0,NORTH"s == toyRobot.Report());
                    };
                };
            };
        };

    	scenario("Exercising robot") = [] {
            given("Robot is placed on a standard board at default location & position") = [] {
                const Board board;
                Robot toyRobot{ board };
                expect(that % "0,0,NORTH"s == toyRobot.Report());

                when("Robot is placed outside board bounds") = [&]() {
	                expect(that % !toyRobot.Place(2, 5, directions::WEST) >> fatal);

                    then("The robot remains at default position & direction") = [&] {
                        expect(that % "0,0,NORTH"s == toyRobot.Report());
                    };
                };
                when("Robot is placed inside board bounds at (2, 4) facing WEST") = [&]() {
                    expect(that % toyRobot.Place(2, 4, directions::WEST));

                    then("The robot reports updated position & direction") = [&] {
                        expect(that % "2,4,WEST"s == toyRobot.Report());
                    };
                };
                when("Robot instructed to turned left") = [&]() {
                    toyRobot.TurnLeft();

                    then("The robot reports same position at (2,4) facing SOUTH ") = [&] {
                        expect(that % "2,4,SOUTH"s == toyRobot.Report());
                    };
                };
                when("Robot instructed to move forward 4 times") = [&]() {
                    for (int i = 0; i < 4; ++i)
                    {
                        expect(that % toyRobot.MoveForward());
                    }
                    then("The robot stops at south edge (2, 0) after 4 steps") = [&] {
                        expect(that % "2,0,SOUTH"s == toyRobot.Report());
                    };
                };
                when("Robot instructed to move forward again") = [&]() {
                	expect(that % !toyRobot.MoveForward());
                    then("The robot does not fall of the edge") = [&] {
                        expect(that % "2,0,SOUTH"s == toyRobot.Report());
                    };
                };
                when("Robot instructed to turn right") = [&]() {
                    toyRobot.TurnRight();
                    then("The robot now faces WEST") = [&] {
                        expect(that % "2,0,WEST"s == toyRobot.Report());
                    };
                };
                when("Robot instructed to move forward twice") = [&]() {
                    toyRobot.MoveForward();
                    toyRobot.MoveForward();
                    then("The robot reports position at origin (0,0) facing WEST") = [&] {
                        expect(that % "0,0,WEST"s == toyRobot.Report());
                    };
                };
            };
        };
    };
};
