#pragma once
#include "MetaCommand.hpp"
#include <vector>
#include <optional>
#include <string>
#include <map>

class CommandRegistry {
public:
    static CommandRegistry& getInstance();
    const MetaCommand* findCommand(const std::string& name) const;
    const std::vector<MetaCommand>& getAllCommands() const { return commands; }
    std::vector<const MetaCommand*> getCommandsByCategory(CommandCategory category) const;
    bool isValidCommand(const std::string& name) const;
    std::string generateHelpText() const;
    std::string generateCategoryHelp(CommandCategory category) const;

private:
    CommandRegistry();
    CommandRegistry(const CommandRegistry&) = delete;
    CommandRegistry& operator=(const CommandRegistry&) = delete;

    void registerAllCommands();
    void registerCommand(MetaCommand&& cmd);

    std::vector<MetaCommand> commands;
    std::map<std::string, size_t> commandIndex;

    static std::string categoryName(CommandCategory category);
};
