#include "../../include/history/ActionHistory.hpp"
#include <iostream>

ActionHistory& ActionHistory::getInstance() {
    static ActionHistory instance;
    return instance;
}

void ActionHistory::recordAction(std::unique_ptr<IAction> action) {
    // Clear redo stack when new action is recorded
    redoStack.clear();

    // Try to merge with previous action if possible
    if (!undoStack.empty()) {
        if (undoStack.back()->merge(action.get())) {
            return; // Action was merged, don't add separately
        }
    }

    undoStack.push_back(std::move(action));
    enforceHistoryLimit();
}

bool ActionHistory::canUndo() const {
    return !undoStack.empty();
}

bool ActionHistory::canRedo() const {
    return !redoStack.empty();
}

void ActionHistory::undo(ISlideRepository* repository) {
    if (!canUndo()) {
        std::cout << "Nothing to undo.\n";
        return;
    }

    auto action = std::move(undoStack.back());
    undoStack.pop_back();

    if (action->canUndo()) {
        action->undo(repository);
        std::cout << "Undone: " << action->getDescription() << "\n";
    } else {
        std::cout << "Cannot undo: " << action->getDescription() << "\n";
    }

    redoStack.push_back(std::move(action));
}

void ActionHistory::redo(ISlideRepository* repository) {
    if (!canRedo()) {
        std::cout << "Nothing to redo.\n";
        return;
    }

    auto action = std::move(redoStack.back());
    redoStack.pop_back();

    action->redo(repository);
    std::cout << "Redone: " << action->getDescription() << "\n";

    undoStack.push_back(std::move(action));
}

void ActionHistory::clear() {
    undoStack.clear();
    redoStack.clear();
}

std::vector<std::string> ActionHistory::getUndoHistory() const {
    std::vector<std::string> history;
    for (const auto& action : undoStack) {
        history.push_back(action->getDescription());
    }
    return history;
}

std::vector<std::string> ActionHistory::getRedoHistory() const {
    std::vector<std::string> history;
    for (const auto& action : redoStack) {
        history.push_back(action->getDescription());
    }
    return history;
}

void ActionHistory::setMaxHistorySize(size_t size) {
    maxHistorySize = size;
    enforceHistoryLimit();
}

size_t ActionHistory::getMaxHistorySize() const {
    return maxHistorySize;
}

void ActionHistory::enforceHistoryLimit() {
    while (undoStack.size() > maxHistorySize) {
        undoStack.erase(undoStack.begin());
    }
}
