#pragma once
#include <functional>
#include <string>
#include "Robot.h"

class Simulator
{
public:
    void Run();
    [[nodiscard]] auto ParseInstruction(const std::string& line) const -> std::pair<std::string, std::vector<std::string>>;
    auto CommandFactory(std::string name, std::vector<std::string> arguments) -> std::function<void(Robot&)>;

private:
    bool m_isInitialised = false;
};
