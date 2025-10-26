#pragma once
#include "../interfaces/ICommand.hpp"
#include "../parser/Parser.hpp"
#include <memory>
#include <stdexcept>

class CommandFactory {
public:
    static std::unique_ptr<ICommand> createCommand(const ParsedCommand& parsed);
};