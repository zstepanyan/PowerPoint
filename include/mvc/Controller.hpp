#pragma once
#include "View.hpp"
#include "../interfaces/ISlideRepository.hpp"
#include "../core/SlideRepository.hpp"
#include <memory>
#include <string>

class Controller {
public:
    Controller();
    explicit Controller(std::unique_ptr<View> view);
    ~Controller() = default;

    // Main application loop
    void run();

    // Process a single command (for testing or scripted input)
    bool processCommand(const std::string& input);

    // Check if application should continue running
    bool isRunning() const { return running; }

    // Get access to repository (for testing)
    ISlideRepository* getRepository() { return repository.get(); }

private:
    std::unique_ptr<View> view;
    std::unique_ptr<SlideRepository> repository;
    bool running;

    // Command execution
    void executeCommand(const std::string& input);

    // Exit handler
    void handleExit();
};
