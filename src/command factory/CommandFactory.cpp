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
    else if (cmd == "delete" || cmd == "deleteslide") {
        if (parsed.args.size() >= 1) {
            return std::make_unique<DeleteSlideCommand>(std::stoi(parsed.args[0]));
        }
        throw std::invalid_argument("delete requires slide index");
    }
    else if (cmd == "move" || cmd == "moveslide") {
        if (parsed.args.size() >= 2) {
            return std::make_unique<MoveSlideCommand>(
                std::stoi(parsed.args[0]), std::stoi(parsed.args[1]));
        }
        throw std::invalid_argument("move requires two arguments: from to");
    }
    else if (cmd == "addshape") {
        if (parsed.args.size() >= 6) {
            return std::make_unique<AddShapeCommand>(
                std::stoi(parsed.args[0]),   // slide index
                parsed.args[1],               // shape type
                std::stod(parsed.args[2]),   // x
                std::stod(parsed.args[3]),   // y
                std::stod(parsed.args[4]),   // width
                std::stod(parsed.args[5]));  // height
        }
        throw std::invalid_argument("addshape requires: <slide> <type> <x> <y> <width> <height>");
    }
    else if (cmd == "removeshape") {
        if (parsed.args.size() >= 2) {
            return std::make_unique<RemoveShapeCommand>(
                std::stoi(parsed.args[0]), std::stoul(parsed.args[1]));
        }
        throw std::invalid_argument("removeshape requires slide index and shape index");
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
    else if (cmd == "edittext") {
        if (parsed.args.size() >= 2) {
            std::string text = "";
            for (size_t i = 1; i < parsed.args.size(); ++i) {
                if (i > 1) text += " ";
                text += parsed.args[i];
            }
            return std::make_unique<EditTextCommand>(
                std::stoi(parsed.args[0]), text);
        }
        throw std::invalid_argument("edittext requires slide index and text");
    }
    else if (cmd == "cleartext") {
        if (parsed.args.size() >= 1) {
            return std::make_unique<ClearTextCommand>(std::stoi(parsed.args[0]));
        }
        throw std::invalid_argument("cleartext requires slide index");
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
    else if (cmd == "undo") {
        return std::make_unique<UndoCommand>();
    }
    else if (cmd == "redo") {
        return std::make_unique<RedoCommand>();
    }
    else if (cmd == "history") {
        return std::make_unique<HistoryCommand>();
    }
    else if (cmd == "sethistory") {
        if (parsed.args.size() >= 1) {
            return std::make_unique<SetHistoryCommand>(std::stoul(parsed.args[0]));
        }
        throw std::invalid_argument("sethistory requires size argument");
    }
    else if (cmd == "export") {
        if (parsed.args.size() >= 2) {
            return std::make_unique<ExportCommand>(
                std::stoi(parsed.args[0]), parsed.args[1]);
        }
        throw std::invalid_argument("export requires slide index and filename");
    }
    else if (cmd == "exportall") {
        if (parsed.args.size() >= 1) {
            return std::make_unique<ExportAllCommand>(parsed.args[0]);
        }
        throw std::invalid_argument("exportall requires directory");
    }
    else if (cmd == "preview") {
        if (parsed.args.size() >= 1) {
            return std::make_unique<PreviewCommand>(std::stoi(parsed.args[0]));
        }
        throw std::invalid_argument("preview requires slide index");
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