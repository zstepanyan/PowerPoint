#include "../../include/metacommand/CommandRegistry.hpp"
#include "../../include/commands/Commands.hpp"
#include "../../include/parser/Parser.hpp"
#include <algorithm>
#include <sstream>

CommandRegistry& CommandRegistry::getInstance() {
    static CommandRegistry instance;
    return instance;
}

CommandRegistry::CommandRegistry() {
    registerAllCommands();
}

void CommandRegistry::registerCommand(MetaCommand&& cmd) {
    size_t index = commands.size();

    // Index by lowercase primary name
    std::string lowerName = cmd.name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    commandIndex[lowerName] = index;

    // Index by lowercase aliases
    for (const auto& alias : cmd.aliases) {
        std::string lowerAlias = alias;
        std::transform(lowerAlias.begin(), lowerAlias.end(), lowerAlias.begin(), ::tolower);
        commandIndex[lowerAlias] = index;
    }

    commands.push_back(std::move(cmd));
}

const MetaCommand* CommandRegistry::findCommand(const std::string& name) const {
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    auto it = commandIndex.find(lowerName);
    if (it != commandIndex.end()) {
        return &commands[it->second];
    }
    return nullptr;
}

bool CommandRegistry::isValidCommand(const std::string& name) const {
    return findCommand(name) != nullptr;
}

std::vector<const MetaCommand*> CommandRegistry::getCommandsByCategory(CommandCategory category) const {
    std::vector<const MetaCommand*> result;
    for (const auto& cmd : commands) {
        if (cmd.category == category) {
            result.push_back(&cmd);
        }
    }
    return result;
}

std::string CommandRegistry::categoryName(CommandCategory category) {
    switch (category) {
        case CommandCategory::Slide: return "Slide Commands";
        case CommandCategory::Shape: return "Shape Commands";
        case CommandCategory::Text: return "Text Commands";
        case CommandCategory::History: return "Undo/Redo";
        case CommandCategory::Export: return "Export";
        case CommandCategory::File: return "File";
        case CommandCategory::System: return "System";
        default: return "Other";
    }
}

std::string CommandRegistry::generateCategoryHelp(CommandCategory category) const {
    std::ostringstream oss;
    oss << categoryName(category) << ":\n";

    auto cmds = getCommandsByCategory(category);
    for (const auto* cmd : cmds) {
        oss << cmd->getHelpText() << "\n";
    }

    return oss.str();
}

std::string CommandRegistry::generateHelpText() const {
    std::ostringstream oss;

    // Order categories logically
    std::vector<CommandCategory> categories = {
        CommandCategory::Slide,
        CommandCategory::Shape,
        CommandCategory::Text,
        CommandCategory::History,
        CommandCategory::Export,
        CommandCategory::File,
        CommandCategory::System
    };

    for (auto category : categories) {
        auto cmds = getCommandsByCategory(category);
        if (!cmds.empty()) {
            oss << generateCategoryHelp(category) << "\n";
        }
    }

    return oss.str();
}

void CommandRegistry::registerAllCommands() {
    // ==================== SLIDE COMMANDS ====================

    registerCommand({
        "create",                                           // name
        {"createslide"},                                    // aliases
        "Create a new slide",                               // description
        "create",                                           // usage
        CommandCategory::Slide,                             // category
        {},                                                 // arguments (none required)
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int num = parsed.args.empty() ? 1 : MetaCommand::parseIntArg(parsed.args[0], "slide number");
            return std::make_unique<CreateSlideCommand>(num);
        },
        true,                                               // isReversible
        true                                                // modifiesState
    });

    registerCommand({
        "delete",
        {"deleteslide"},
        "Delete a slide",
        "delete <slide>",
        CommandCategory::Slide,
        {ArgDef("slide", ArgType::Integer, true, "", "Slide number to delete")},
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int idx = MetaCommand::parseIntArg(parsed.args[0], "slide number");
            return std::make_unique<DeleteSlideCommand>(idx);
        },
        true,
        true
    });

    registerCommand({
        "move",
        {"moveslide"},
        "Move slide from one position to another",
        "move <from> <to>",
        CommandCategory::Slide,
        {
            ArgDef("from", ArgType::Integer, true, "", "Source position"),
            ArgDef("to", ArgType::Integer, true, "", "Destination position")
        },
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int from = MetaCommand::parseIntArg(parsed.args[0], "from position");
            int to = MetaCommand::parseIntArg(parsed.args[1], "to position");
            return std::make_unique<MoveSlideCommand>(from, to);
        },
        true,
        true
    });

    registerCommand({
        "list",
        {"listslides"},
        "List all slides",
        "list",
        CommandCategory::Slide,
        {},
        [](const ParsedCommand&) -> std::unique_ptr<ICommand> {
            return std::make_unique<ListSlidesCommand>();
        },
        false,
        false
    });

    registerCommand({
        "display",
        {},
        "Display slide details",
        "display <slide>",
        CommandCategory::Slide,
        {ArgDef("slide", ArgType::Integer, true, "", "Slide number to display")},
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int idx = MetaCommand::parseIntArg(parsed.args[0], "slide number");
            return std::make_unique<DisplaySlideCommand>(idx);
        },
        false,
        false
    });

    // ==================== SHAPE COMMANDS ====================

    registerCommand({
        "addshape",
        {},
        "Add shape to slide",
        "addshape <slide> <type> <x> <y> <width> <height>",
        CommandCategory::Shape,
        {
            ArgDef("slide", ArgType::Integer, true, "", "Slide number"),
            ArgDef("type", ArgType::String, true, "", "Shape type (Rectangle, Circle, Triangle)"),
            ArgDef("x", ArgType::Double, true, "", "X position"),
            ArgDef("y", ArgType::Double, true, "", "Y position"),
            ArgDef("width", ArgType::Double, true, "", "Width"),
            ArgDef("height", ArgType::Double, true, "", "Height")
        },
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int slide = MetaCommand::parseIntArg(parsed.args[0], "slide number");
            std::string type = parsed.args[1];
            double x = MetaCommand::parseDoubleArg(parsed.args[2], "x");
            double y = MetaCommand::parseDoubleArg(parsed.args[3], "y");
            double w = MetaCommand::parseDoubleArg(parsed.args[4], "width");
            double h = MetaCommand::parseDoubleArg(parsed.args[5], "height");
            return std::make_unique<AddShapeCommand>(slide, type, x, y, w, h);
        },
        true,
        true
    });

    registerCommand({
        "removeshape",
        {},
        "Remove shape from slide",
        "removeshape <slide> <shape#>",
        CommandCategory::Shape,
        {
            ArgDef("slide", ArgType::Integer, true, "", "Slide number"),
            ArgDef("shape#", ArgType::Integer, true, "", "Shape index (1-based)")
        },
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int slide = MetaCommand::parseIntArg(parsed.args[0], "slide number");
            size_t shape = static_cast<size_t>(MetaCommand::parseIntArg(parsed.args[1], "shape index"));
            return std::make_unique<RemoveShapeCommand>(slide, shape);
        },
        true,
        true
    });

    // ==================== TEXT COMMANDS ====================

    registerCommand({
        "addtext",
        {},
        "Add text to slide (must be empty)",
        "addtext <slide> <text>",
        CommandCategory::Text,
        {
            ArgDef("slide", ArgType::Integer, true, "", "Slide number"),
            ArgDef("text", ArgType::Text, true, "", "Text content")
        },
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int slide = MetaCommand::parseIntArg(parsed.args[0], "slide number");
            std::string text = MetaCommand::joinTextArgs(parsed.args, 1);
            return std::make_unique<AddTextCommand>(slide, text);
        },
        true,
        true
    });

    registerCommand({
        "edittext",
        {},
        "Modify existing text",
        "edittext <slide> <text>",
        CommandCategory::Text,
        {
            ArgDef("slide", ArgType::Integer, true, "", "Slide number"),
            ArgDef("text", ArgType::Text, true, "", "New text content")
        },
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int slide = MetaCommand::parseIntArg(parsed.args[0], "slide number");
            std::string text = MetaCommand::joinTextArgs(parsed.args, 1);
            return std::make_unique<EditTextCommand>(slide, text);
        },
        true,
        true
    });

    registerCommand({
        "cleartext",
        {},
        "Clear slide text",
        "cleartext <slide>",
        CommandCategory::Text,
        {ArgDef("slide", ArgType::Integer, true, "", "Slide number")},
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int slide = MetaCommand::parseIntArg(parsed.args[0], "slide number");
            return std::make_unique<ClearTextCommand>(slide);
        },
        true,
        true
    });

    // ==================== UNDO/REDO COMMANDS ====================

    registerCommand({
        "undo",
        {},
        "Undo last action",
        "undo",
        CommandCategory::History,
        {},
        [](const ParsedCommand&) -> std::unique_ptr<ICommand> {
            return std::make_unique<UndoCommand>();
        },
        false,
        true
    });

    registerCommand({
        "redo",
        {},
        "Redo last undone action",
        "redo",
        CommandCategory::History,
        {},
        [](const ParsedCommand&) -> std::unique_ptr<ICommand> {
            return std::make_unique<RedoCommand>();
        },
        false,
        true
    });

    registerCommand({
        "history",
        {},
        "Show action history",
        "history",
        CommandCategory::History,
        {},
        [](const ParsedCommand&) -> std::unique_ptr<ICommand> {
            return std::make_unique<HistoryCommand>();
        },
        false,
        false
    });

    registerCommand({
        "sethistory",
        {},
        "Set max history size",
        "sethistory <size>",
        CommandCategory::History,
        {ArgDef("size", ArgType::Integer, true, "", "Maximum history size")},
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            size_t size = static_cast<size_t>(MetaCommand::parseIntArg(parsed.args[0], "history size"));
            return std::make_unique<SetHistoryCommand>(size);
        },
        false,
        false
    });

    // ==================== EXPORT COMMANDS ====================

    registerCommand({
        "export",
        {},
        "Export slide to SVG",
        "export <slide> <file>",
        CommandCategory::Export,
        {
            ArgDef("slide", ArgType::Integer, true, "", "Slide number"),
            ArgDef("file", ArgType::FilePath, true, "", "Output file path")
        },
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int slide = MetaCommand::parseIntArg(parsed.args[0], "slide number");
            return std::make_unique<ExportCommand>(slide, parsed.args[1]);
        },
        false,
        false
    });

    registerCommand({
        "exportall",
        {},
        "Export all slides to directory",
        "exportall <dir>",
        CommandCategory::Export,
        {ArgDef("dir", ArgType::FilePath, true, "", "Output directory")},
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            return std::make_unique<ExportAllCommand>(parsed.args[0]);
        },
        false,
        false
    });

    registerCommand({
        "preview",
        {},
        "Preview slide SVG in console",
        "preview <slide>",
        CommandCategory::Export,
        {ArgDef("slide", ArgType::Integer, true, "", "Slide number")},
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            int slide = MetaCommand::parseIntArg(parsed.args[0], "slide number");
            return std::make_unique<PreviewCommand>(slide);
        },
        false,
        false
    });

    // ==================== FILE COMMANDS ====================

    registerCommand({
        "save",
        {},
        "Save presentation to JSON",
        "save <filename>",
        CommandCategory::File,
        {ArgDef("filename", ArgType::FilePath, true, "", "Output file path")},
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            return std::make_unique<SaveCommand>(parsed.args[0]);
        },
        false,
        false
    });

    registerCommand({
        "load",
        {},
        "Load presentation from JSON",
        "load <filename>",
        CommandCategory::File,
        {ArgDef("filename", ArgType::FilePath, true, "", "Input file path")},
        [](const ParsedCommand& parsed) -> std::unique_ptr<ICommand> {
            return std::make_unique<LoadCommand>(parsed.args[0]);
        },
        false,
        true
    });

    // ==================== SYSTEM COMMANDS ====================

    registerCommand({
        "exit",
        {"quit"},
        "Exit the application",
        "exit",
        CommandCategory::System,
        {},
        [](const ParsedCommand&) -> std::unique_ptr<ICommand> {
            return std::make_unique<ExitCommand>();
        },
        false,
        false
    });

    registerCommand({
        "help",
        {"?"},
        "Show help message",
        "help",
        CommandCategory::System,
        {},
        nullptr,  // Help is handled specially by controller
        false,
        false
    });
}
