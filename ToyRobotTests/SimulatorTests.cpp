#include "Simulator.h"
#include "boost/ut.hpp"

using namespace boost::ut;
using namespace literals;
using namespace bdd;
using namespace std::literals::string_literals;

suite SimulatorTests = [] {
    feature("Simulator") = []
    {
        scenario("Instruction parsing") = [] {
            given("I have a simulator") = [] {
	            const Simulator simulator;
                when("Parsing empty instruction") = [&] {
                    then("invalid argument exception is thrown") = [&] {
                        expect(throws<std::invalid_argument>([&] {
                            auto [name, arguments] = simulator.ParseInstruction("");
                            })) << "throws invalid_argument";
                    };
                };
                when("Parsing instruction in invalid format") = [&] {
                    then("invalid argument exception is thrown") = [&] {
                        expect(throws<std::invalid_argument>([&] {
                            auto [name, arguments] = simulator.ParseInstruction("Place 2 3 north");
                            })) << "throws invalid_argument";
                    };
                };
                when("Parsing no-argument instruction") = [&] {
                    auto [name, arguments] = simulator.ParseInstruction("Foo");
                    then("Correct name and empty arguments list") = [&] {
                        expect(that % name == "Foo"s);
                        expect(that% arguments.empty());
                    };
                };
                when("Parsing instruction with comma separated arguments") = [&] {
                    auto [name, arguments] = simulator.ParseInstruction("Foo 1,bar,5.420,0xdeadbeaf");
                    then("Correct name and matching arguments list") = [&] {
                        expect(that % name == "Foo"s);
                        expect(that % 4 == arguments.size());
                        expect(that % "1"s == arguments[0]);
                        expect(that % "bar"s == arguments[1]);
                        expect(that % "5.420"s == arguments[2]);
                        expect(that % "0xdeadbeaf"s == arguments[3]);
                    };
                };
            };
        };

        scenario("Build executable command from instruction") = [] {
            given("I have a simulator with a toy robot on a default board") = [] {
                Simulator simulator;
                const Board board;
            	Robot toyRobot{ board };
                when("Unknown command name") = [&] {
                    auto [name, arguments] = simulator.ParseInstruction("foo");
                    then("invalid argument exception is thrown") = [&] {
                        expect(throws<std::invalid_argument>([&] {
                            auto command = simulator.CommandFactory(name, arguments);
                            })) << "throws invalid_argument";
                    };
                };
                when("Non placement command before robot was placed") = [&] {
                    auto [name, arguments] = simulator.ParseInstruction("RIGHT");
                    then("invalid argument exception is thrown") = [&] {
                        expect(throws<std::invalid_argument>([&] {
                            auto command = simulator.CommandFactory(name, arguments);
                            })) << "throws invalid_argument";
                    };
                };
                when("Invalid argument count for PLACE command") = [&] {
                    auto [name, arguments] = simulator.ParseInstruction("PLACE 2,2");
                    then("invalid argument exception is thrown") = [&] {
                        expect(throws<std::invalid_argument>([&] {
                            auto command = simulator.CommandFactory(name, arguments);
                            })) << "throws invalid_argument";
                    };
                };
                when("Invalid coordinate argument for PLACE command") = [&] {
                    auto [name, arguments] = simulator.ParseInstruction("PLACE one,one,NORTH");
                    then("invalid argument exception is thrown") = [&] {
                        expect(throws<std::exception>([&] {
                            auto command = simulator.CommandFactory(name, arguments);
                            })) << "throws exception";
                    };
                };
                when("Invalid direction argument for PLACE command") = [&] {
                    auto [name, arguments] = simulator.ParseInstruction("PLACE 0,0,NORTHEAST");
                    then("invalid argument exception is thrown") = [&] {
                        expect(throws<std::invalid_argument>([&] {
                            auto command = simulator.CommandFactory(name, arguments);
                            })) << "throws invalid_argument";
                    };
                };
                when("valid (case insensitive) PLACE command") = [&] {
                    auto [name, arguments] = simulator.ParseInstruction("PlaCe 2,2,NOrtH");
                    const auto command = simulator.CommandFactory(name, arguments);
                    expect(that % command);
                    then("PLACE command is executed correctly") = [&] {
                        command(toyRobot);
                        expect(that % toyRobot.Report() == "2,2,NORTH"s);
                    };
                };
                when("Valid commands after robot has been correctly placed") = [&] {
                    std::vector<std::pair<const std::string, const std::string>> instructionListWithResults = 
                    {{
                        {"Place 0,0,west"s, "0,0,WEST"s},
                        {"Right"s, "0,0,NORTH"s},
                        {"MOve"s, "0,1,NORTH"s},
                        {"LEFt"s, "0,1,WEST"s},
                    }};
                    for (auto& pair: instructionListWithResults)
                    {
                        auto& [instruction, expectedOutput] = pair;
                        auto [name, arguments] = simulator.ParseInstruction(instruction);
                        const auto command = simulator.CommandFactory(name, arguments);
                        then(name + "command executed correctly") = [&] {
                            expect(that % command);
                            command(toyRobot);
                            expect(that% toyRobot.Report() == expectedOutput);
                        };
                    }
                };
            };
        };
    };
};
