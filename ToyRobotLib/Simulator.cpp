#include "Simulator.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>

#include "Board.h"
#include "Robot.h"

namespace
{
	std::string ToUpper(std::string s) {
		std::ranges::transform(s, s.begin(), 
			[](unsigned char c) { return std::toupper(c); });
		return s;
	}

	std::vector<std::string> Parse(const std::string& input, const char delimiter)
	{
		std::istringstream ss(input);
		std::string token;
		std::vector<std::string> tokens;
		while (std::getline(ss, token, delimiter)) {
			tokens.push_back(token);
		}
		return tokens;
	}
}

void Simulator::Run()
{
	const Board board;
	Robot toyRobot{ board };
	std::string line;
	while (std::getline(std::cin, line))
		try
	{
		auto [name, arguments] = ParseInstruction(line);
		CommandFactory(name, arguments)(toyRobot);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "ERROR: " << ex.what() << std::endl;
	}
}

auto Simulator::ParseInstruction(const std::string& line) const -> std::pair<std::string, std::vector<std::string>>
{
	auto tokens = Parse(line, ' ');
	if (tokens.size() == 2)
	{
		auto arguments = Parse(tokens[1], ',');
		return std::make_pair(move(tokens[0]), move(arguments));
	}
	if (tokens.size() == 1)
	{
		return std::make_pair(move(tokens[0]), std::vector<std::string>{});
	}
	throw std::invalid_argument("Unrecognized instruction: " + line );
}

auto Simulator::CommandFactory(std::string name, std::vector<std::string> arguments) -> std::function<void(Robot&)>
{
	const auto command = ToUpper(std::move(name));

	if (!m_isInitialised && command != "PLACE")
		throw std::invalid_argument("Instruction ignored before proper placement: " + command);

	if (command == "PLACE")
	{
		if (arguments.size() != 3)
			throw std::invalid_argument("PLACE instruction called with incorrect number of arguments.");

		const int x = std::stoi(arguments[0]);
		const int y = std::stoi(arguments[1]);
		const directions::Direction direction = directions::FromString(ToUpper(arguments[2]));

		return  [&, x, y, direction](auto& robot) {
			if (robot.Place(x, y, direction))
				m_isInitialised = true;
		};	
	}

	if (command == "MOVE")
		return [](auto& robot) { robot.MoveForward(); };

	if (command == "LEFT")
		return [](auto& robot) { robot.TurnLeft(); };

	if (command == "RIGHT")
		return [](auto& robot) { robot.TurnRight(); };

	if (command == "REPORT")
		return [](auto& robot) { std::cout << "Output: " << robot.Report() << std::endl; };

	throw std::invalid_argument("Unrecognized command: " + command);
}
