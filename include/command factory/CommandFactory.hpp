#pragma once
#include "../interfaces/ICommand.hpp"
#include "../parser/Parser.hpp"
#include "../metacommand/CommandRegistry.hpp"
#include <memory>
#include <stdexcept>

class CommandFactory {
public:
    static std::unique_ptr<ICommand> createCommand(const ParsedCommand& parsed);
    static bool commandExists(const std::string& name);
    static const MetaCommand* getCommandMeta(const std::string& name);
};
