#include "../../include/command factory/CommandFactory.hpp"
#include "../../include/commands/Commands.hpp"
#include <algorithm>

std::unique_ptr<ICommand> CommandFactory::createCommand(const ParsedCommand& parsed) {
    std::string cmd = parsed.command;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    const MetaCommand* meta = CommandRegistry::getInstance().findCommand(cmd);

    if (!meta) {
        throw std::invalid_argument("Unknown command: " + parsed.command);
    }

    std::string error;
    if (!meta->validateArgs(parsed.args, error)) {
        throw std::invalid_argument(error);
    }

    if (!meta->creator) {
        throw std::invalid_argument("Command '" + parsed.command + "' has no implementation");
    }

    return meta->creator(parsed);
}

bool CommandFactory::commandExists(const std::string& name) {
    return CommandRegistry::getInstance().isValidCommand(name);
}

const MetaCommand* CommandFactory::getCommandMeta(const std::string& name) {
    return CommandRegistry::getInstance().findCommand(name);
}
