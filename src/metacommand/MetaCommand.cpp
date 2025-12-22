#include "../../include/metacommand/MetaCommand.hpp"
#include <algorithm>
#include <sstream>
#include <stdexcept>

bool MetaCommand::matches(const std::string& cmd) const {
    std::string lowerCmd = cmd;
    std::transform(lowerCmd.begin(), lowerCmd.end(), lowerCmd.begin(), ::tolower);

    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    if (lowerCmd == lowerName) {
        return true;
    }

    for (const auto& alias : aliases) {
        std::string lowerAlias = alias;
        std::transform(lowerAlias.begin(), lowerAlias.end(), lowerAlias.begin(), ::tolower);
        if (lowerCmd == lowerAlias) {
            return true;
        }
    }

    return false;
}

bool MetaCommand::validateArgs(const std::vector<std::string>& args, std::string& error) const {
    size_t minRequired = minArgs();

    if (args.size() < minRequired) {
        std::ostringstream oss;
        oss << name << " requires at least " << minRequired << " argument(s). Usage: " << usage;
        error = oss.str();
        return false;
    }

    size_t argIndex = 0;
    for (const auto& argDef : arguments) {
        if (argIndex >= args.size()) {
            if (argDef.required) {
                error = "Missing required argument: " + argDef.name;
                return false;
            }
            break;
        }

        if (argDef.type == ArgType::Text) {
            break;
        }

        const std::string& arg = args[argIndex];

        try {
            switch (argDef.type) {
                case ArgType::Integer:
                    std::stoi(arg);
                    break;
                case ArgType::Double:
                    std::stod(arg);
                    break;
                case ArgType::String:
                case ArgType::FilePath:
                    break;
                default:
                    break;
            }
        } catch (const std::exception&) {
            std::ostringstream oss;
            oss << "Invalid " << argDef.name << ": expected ";
            switch (argDef.type) {
                case ArgType::Integer: oss << "integer"; break;
                case ArgType::Double: oss << "number"; break;
                default: oss << "string"; break;
            }
            oss << ", got '" << arg << "'";
            error = oss.str();
            return false;
        }

        ++argIndex;
    }

    return true;
}

size_t MetaCommand::minArgs() const {
    size_t count = 0;
    for (const auto& arg : arguments) {
        if (arg.required) {
            ++count;
        }
    }
    return count;
}

size_t MetaCommand::maxArgs() const {
    if (!arguments.empty() && arguments.back().type == ArgType::Text) {
        return SIZE_MAX;
    }
    return arguments.size();
}

std::string MetaCommand::getHelpText() const {
    std::ostringstream oss;
    oss << "  " << usage;

    size_t usageLen = usage.length();
    if (usageLen < 35) {
        oss << std::string(35 - usageLen, ' ');
    } else {
        oss << " ";
    }

    oss << "- " << description;

    if (!aliases.empty()) {
        oss << " (aliases: ";
        for (size_t i = 0; i < aliases.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << aliases[i];
        }
        oss << ")";
    }

    return oss.str();
}

int MetaCommand::parseIntArg(const std::string& arg, const std::string& argName) {
    try {
        return std::stoi(arg);
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid " + argName + ": expected integer, got '" + arg + "'");
    }
}

double MetaCommand::parseDoubleArg(const std::string& arg, const std::string& argName) {
    try {
        return std::stod(arg);
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid " + argName + ": expected number, got '" + arg + "'");
    }
}

std::string MetaCommand::joinTextArgs(const std::vector<std::string>& args, size_t startIndex) {
    std::string result;
    for (size_t i = startIndex; i < args.size(); ++i) {
        if (i > startIndex) result += " ";
        result += args[i];
    }
    return result;
}
