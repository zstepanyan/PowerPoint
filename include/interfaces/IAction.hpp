#pragma once
#include "ICommand.hpp"
#include <memory>
#include <string>

class IAction : public ICommand {
public:
    virtual ~IAction() = default;

    // Inherited from ICommand
    virtual void execute(ISlideRepository* repository) override = 0;
    virtual std::string getName() const override = 0;

    // Undo/Redo methods
    virtual void undo(ISlideRepository* repository) = 0;
    virtual void redo(ISlideRepository* repository) { execute(repository); }

    // Description for history display
    virtual std::string getDescription() const = 0;

    // Check if this action supports undo
    virtual bool canUndo() const = 0;

    // Optional: merge consecutive similar actions (e.g., typing)
    virtual bool merge(const IAction* other) { (void)other; return false; }
};
