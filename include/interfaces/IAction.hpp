#pragma once
#include "ICommand.hpp"
#include <memory>
#include <string>

class IAction : public ICommand {
public:
    virtual ~IAction() = default;
    virtual void execute(ISlideRepository* repository) override = 0;
    virtual std::string getName() const override = 0;
    virtual void undo(ISlideRepository* repository) = 0;
    virtual void redo(ISlideRepository* repository) { execute(repository); }
    virtual std::string getDescription() const = 0;
    virtual bool canUndo() const = 0;
    virtual bool merge(const IAction* other) { (void)other; return false; }
};
