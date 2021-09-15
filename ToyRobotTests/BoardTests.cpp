#include "Board.h"
#include "boost/ut.hpp"

using namespace boost::ut;
using namespace bdd;

suite BoardTests = [] {
    feature("Board") = []
    {
        scenario("Checking board bounds for default board") = [] {
            given("I have a default board") = [] {
                const Board board;
                expect((that % 5 == board.Width()) >> fatal);
                expect((that % 5 == board.Length()) >> fatal);

                when("a coordinate is negative") = [=]() mutable {
                    then("CheckBounds fails") = [&] {
                        expect(that % !board.CheckBounds(0, -1));
                    };
                };
                when("x coordinate is equal to width") = [=]() mutable {
                    then("CheckBounds fails") = [&] {
                        expect(that % !board.CheckBounds(5, 1));
                    };
                };
                when("(x, y) is at origin (0, 0)") = [=]() mutable {
                    then("CheckBounds succeeds") = [&] {
                        expect(that % board.CheckBounds(0, 0));
                    };
                };
                when("(x, y) is within bounds") = [=]() mutable {
                    then("CheckBounds succeeds") = [&] {
                        expect(that % board.CheckBounds(2, 3));
                    };
                };
            };
        };

        scenario("Checking board bounds for a custom board") = [] {
            given("I have a custom board") = [] {
                const Board board(6, 9);
                expect((that % 6 == board.Width()) >> fatal);
                expect((that % 9 == board.Length()) >> fatal);

                when("a coordinate is negative") = [=]() mutable {
                    then("CheckBounds fails") = [&] {
                        expect(that % !board.CheckBounds(-1, 0));
                    };
                };
                when("y coordinate is equal to length") = [=]() mutable {
                    then("CheckBounds fails") = [&] {
                        expect(that % !board.CheckBounds(2, board.Length()));
                    };
                };
                when("(x, y) is at origin (0, 0)") = [=]() mutable {
                    then("CheckBounds succeeds") = [&] {
                        expect(that % board.CheckBounds(0, 0));
                    };
                };
                when("(x, y) is within bounds") = [=]() mutable {
                    then("CheckBounds succeeds") = [&] {
                        expect(that % board.CheckBounds(5, 8));
                    };
                };
            };
        };
    };
};

