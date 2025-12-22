#pragma once
#include "../interfaces/IAction.hpp"
#include "../interfaces/ISlideRepository.hpp"
#include <vector>
#include <memory>
#include <string>

class ActionHistory {
public:
    static ActionHistory& getInstance();
    void recordAction(std::unique_ptr<IAction> action);
    bool canUndo() const;
    bool canRedo() const;
    void undo(ISlideRepository* repository);
    void redo(ISlideRepository* repository);
    void clear();
    std::vector<std::string> getUndoHistory() const;
    std::vector<std::string> getRedoHistory() const;
    void setMaxHistorySize(size_t size);
    size_t getMaxHistorySize() const;

private:
    ActionHistory() = default;
    ActionHistory(const ActionHistory&) = delete;
    ActionHistory& operator=(const ActionHistory&) = delete;

    std::vector<std::unique_ptr<IAction>> undoStack;
    std::vector<std::unique_ptr<IAction>> redoStack;
    size_t maxHistorySize = 50;

    void enforceHistoryLimit();
};
