#include "../../include/parser/Parser.hpp"
#include "../../include/metacommand/CommandRegistry.hpp"

ParsedCommand Parser::parse(const std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        throw std::runtime_error("Empty command");
    }
    return parseCommand(tokens);
}

ParsedCommand Parser::parseCommand(const std::vector<std::string>& tokens) {
    ParsedCommand cmd;
    cmd.command = tokens[0];

    for (size_t i = 1; i < tokens.size(); ++i) {
        cmd.args.push_back(tokens[i]);
    }

    return cmd;
}

bool Parser::isValidCommand(const std::string& cmd) {
    return CommandRegistry::getInstance().isValidCommand(cmd);
}

bool Parser::validateCommand(const ParsedCommand& parsed, std::string& error) {
    const MetaCommand* meta = CommandRegistry::getInstance().findCommand(parsed.command);

    if (!meta) {
        error = "Unknown command: " + parsed.command;
        return false;
    }

    return meta->validateArgs(parsed.args, error);
}

std::string Parser::getCommandHelp(const std::string& cmd) {
    const MetaCommand* meta = CommandRegistry::getInstance().findCommand(cmd);

    if (!meta) {
        return "Unknown command: " + cmd;
    }

    return meta->getHelpText();
}

std::string Parser::getFullHelp() {
    return CommandRegistry::getInstance().generateHelpText();
}
