#include "../../include/parser/Parser.hpp"

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
    static const std::vector<std::string> validCommands = {
        "create", "move", "addshape", "addtext", "list", "display", 
        "save", "load", "exit", "help"
    };
    
    for (const auto& valid : validCommands) {
        if (cmd == valid) return true;
    }
 
    return false;
}