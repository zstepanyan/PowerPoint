#include "../../include/mvc/Controller.hpp"
#include "../../include/parser/Tokenizer.hpp"
#include "../../include/parser/Parser.hpp"
#include "../../include/metacommand/CommandRegistry.hpp"
#include "../../include/interfaces/ICommand.hpp"
#include <algorithm>
#include <iostream>

Controller::Controller()
    : view(std::make_unique<View>())
    , repository(std::make_unique<SlideRepository>())
    , running(true) {
}

Controller::Controller(std::unique_ptr<View> customView)
    : view(std::move(customView))
    , repository(std::make_unique<SlideRepository>())
    , running(true) {
}

void Controller::run() {
    view->showWelcome();

    while (running && view->hasInput()) {
        view->showPrompt();
        std::string input = view->getInput();

        if (input.empty()) {
            continue;
        }

        processCommand(input);
    }
}

bool Controller::processCommand(const std::string& input) {
    if (input.empty()) {
        return true;
    }

    try {
        executeCommand(input);
        return true;
    } catch (const std::exception& e) {
        view->showError(e.what());
        return false;
    }
}

void Controller::executeCommand(const std::string& input) {
    auto tokens = Tokenizer::tokenizeString(input);
    auto parsedCommand = Parser::parse(tokens);

    std::string cmd = parsedCommand.command;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    if (handleSpecialCommand(cmd, parsedCommand)) {
        return;
    }

    const MetaCommand* meta = CommandRegistry::getInstance().findCommand(cmd);

    if (!meta) {
        throw std::invalid_argument("Unknown command: " + parsedCommand.command + ". Type 'help' for available commands.");
    }

    std::string validationError;
    if (!meta->validateArgs(parsedCommand.args, validationError)) {
        throw std::invalid_argument(validationError);
    }

    if (meta->creator) {
        auto command = meta->creator(parsedCommand);
        command->execute(repository.get());
    }
}

bool Controller::handleSpecialCommand(const std::string& cmd, const ParsedCommand& parsed) {
    (void)parsed;

    if (cmd == "exit" || cmd == "quit") {
        handleExit();
        return true;
    }

    if (cmd == "help" || cmd == "?") {
        showHelp();
        return true;
    }

    return false;
}

void Controller::showHelp() {
    std::cout << "================================\n";
    std::cout << "    SlideEditor Commands\n";
    std::cout << "================================\n\n";
    std::cout << Parser::getFullHelp();
    std::cout << "================================\n";
}

void Controller::handleExit() {
    view->showGoodbye();
    running = false;
}
