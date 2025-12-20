#include "../../include/mvc/Controller.hpp"
#include "../../include/parser/Tokenizer.hpp"
#include "../../include/parser/Parser.hpp"
#include "../../include/command factory/CommandFactory.hpp"
#include <algorithm>

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

    // Check for exit command
    std::string cmd = parsedCommand.command;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    if (cmd == "exit" || cmd == "quit") {
        handleExit();
        return;
    }

    // Create and execute command
    auto command = CommandFactory::createCommand(parsedCommand);
    command->execute(repository.get());
}

void Controller::handleExit() {
    view->showGoodbye();
    running = false;
}
