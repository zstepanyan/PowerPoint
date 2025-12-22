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
    static bool isValidCommand(const std::string& cmd);
    static bool validateCommand(const ParsedCommand& parsed, std::string& error);
    static std::string getCommandHelp(const std::string& cmd);
    static std::string getFullHelp();

private:
    enum class State {
        Start,
        CommandName,
        CommandArgs,
        End
    };

    static ParsedCommand parseCommand(const std::vector<std::string>& tokens);
};
