#include "../../include/command factory/CommandFactory.hpp"
#include "../../include/commands/Commands.hpp"
#include <algorithm>

std::unique_ptr<ICommand> CommandFactory::createCommand(const ParsedCommand& parsed) {
    std::string cmd = parsed.command;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    
    if (cmd == "create" || cmd == "createslide") {
        return std::make_unique<CreateSlideCommand>(parsed.args.size() > 0 ? 
            std::stoi(parsed.args[0]) : 1);
    }
    else if (cmd == "move" || cmd == "moveslide") {
        if (parsed.args.size() >= 2) {
            return std::make_unique<MoveSlideCommand>(
                std::stoi(parsed.args[0]), std::stoi(parsed.args[1]));
        }
        throw std::invalid_argument("move requires two arguments: from to");
    }
    else if (cmd == "addshape") {
        if (parsed.args.size() >= 2) {
            return std::make_unique<AddShapeCommand>(
                std::stoi(parsed.args[0]), parsed.args[1]);
        }
        throw std::invalid_argument("addshape requires slide index and shape type");
    }
    else if (cmd == "addtext") {
        if (parsed.args.size() >= 2) {
            std::string text = "";
            for (size_t i = 1; i < parsed.args.size(); ++i) {
                if (i > 1) text += " ";
                text += parsed.args[i];
            }
            return std::make_unique<AddTextCommand>(
                std::stoi(parsed.args[0]), text);
        }
        throw std::invalid_argument("addtext requires slide index and text");
    }
    else if (cmd == "list" || cmd == "listslides") {
        return std::make_unique<ListSlidesCommand>();
    }
    else if (cmd == "display") {
        if (parsed.args.size() >= 1) {
            return std::make_unique<DisplaySlideCommand>(std::stoi(parsed.args[0]));
        }
        throw std::invalid_argument("display requires slide index");
    }
    else if (cmd == "save") {
        if (parsed.args.size() >= 1) {
            return std::make_unique<SaveCommand>(parsed.args[0]);
        }
        throw std::invalid_argument("save requires filename");
    }
    else if (cmd == "load") {
        if (parsed.args.size() >= 1) {
            return std::make_unique<LoadCommand>(parsed.args[0]);
        }
        throw std::invalid_argument("load requires filename");
    }
    else if (cmd == "exit" || cmd == "quit") {
        return std::make_unique<ExitCommand>();
    }
    else {
        throw std::invalid_argument("Unknown command: " + parsed.command);
    }
}