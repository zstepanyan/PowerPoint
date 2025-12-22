#pragma once
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <optional>

class ICommand;
class ISlideRepository;
struct ParsedCommand;

enum class ArgType {
    Integer,
    Double,
    String,
    Text,
    FilePath
};

struct ArgDef {
    std::string name;
    ArgType type;
    bool required;
    std::string defaultValue;
    std::string description;

    ArgDef(const std::string& n, ArgType t, bool req = true,
           const std::string& def = "", const std::string& desc = "")
        : name(n), type(t), required(req), defaultValue(def), description(desc) {}
};

enum class CommandCategory {
    Slide,
    Shape,
    Text,
    History,
    Export,
    File,
    System
};

using CommandCreator = std::function<std::unique_ptr<ICommand>(const ParsedCommand&)>;

struct MetaCommand {
    std::string name;
    std::vector<std::string> aliases;
    std::string description;
    std::string usage;
    CommandCategory category;
    std::vector<ArgDef> arguments;
    CommandCreator creator;
    bool isReversible;
    bool modifiesState;

    bool matches(const std::string& cmd) const;
    bool validateArgs(const std::vector<std::string>& args, std::string& error) const;
    size_t minArgs() const;
    size_t maxArgs() const;
    std::string getHelpText() const;
    static int parseIntArg(const std::string& arg, const std::string& argName);
    static double parseDoubleArg(const std::string& arg, const std::string& argName);
    static std::string joinTextArgs(const std::vector<std::string>& args, size_t startIndex);
};
