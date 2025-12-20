#pragma once
#include <vector>
#include <string>
#include <stdexcept>

struct ParsedCommand {
    std::string command;
    std::vector<std::string> args;
};

class Parser {
public:
    static ParsedCommand parse(const std::vector<std::string>& tokens);

private:
    enum class State {
        Start,
        CommandName,
        CommandArgs,
        End
    };

    static ParsedCommand parseCommand(const std::vector<std::string>& tokens);
    static bool isValidCommand(const std::string& cmd);
};