#pragma once
#include "../interfaces/IAction.hpp"
#include "../interfaces/ISlideRepository.hpp"
#include <vector>
#include <memory>
#include <string>

class ActionHistory {
public:
    static ActionHistory& getInstance();

    // Record a new action (clears redo stack)
    void recordAction(std::unique_ptr<IAction> action);

    // Undo/Redo operations
    bool canUndo() const;
    bool canRedo() const;
    void undo(ISlideRepository* repository);
    void redo(ISlideRepository* repository);

    // Clear all history
    void clear();

    // Get history for display
    std::vector<std::string> getUndoHistory() const;
    std::vector<std::string> getRedoHistory() const;

    // Configure max history size
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
