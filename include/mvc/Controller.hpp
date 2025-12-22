#pragma once
#include "View.hpp"
#include "../interfaces/ISlideRepository.hpp"
#include "../core/SlideRepository.hpp"
#include "../metacommand/MetaCommand.hpp"
#include <memory>
#include <string>

struct ParsedCommand;

class Controller {
public:
    Controller();
    explicit Controller(std::unique_ptr<View> view);
    ~Controller() = default;
    void run();
    bool processCommand(const std::string& input);
    bool isRunning() const { return running; }
    ISlideRepository* getRepository() { return repository.get(); }

private:
    std::unique_ptr<View> view;
    std::unique_ptr<SlideRepository> repository;
    bool running;

    void executeCommand(const std::string& input);
    bool handleSpecialCommand(const std::string& cmd, const ParsedCommand& parsed);
    void showHelp();
    void handleExit();
};
