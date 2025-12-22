#pragma once
#include "../interfaces/IAction.hpp"
#include "../interfaces/ISlideRepository.hpp"
#include "../core/Slide.hpp"
#include "../core/SlideMemento.hpp"
#include <memory>
#include <string>

class CreateSlideAction : public IAction {
public:
    CreateSlideAction() = default;
    void execute(ISlideRepository* repository) override;
    void undo(ISlideRepository* repository) override;
    void redo(ISlideRepository* repository) override;
    std::string getName() const override { return "CreateSlide"; }
    std::string getDescription() const override;
    bool canUndo() const override { return createdIndex >= 0; }

private:
    int createdIndex = -1;
    std::unique_ptr<Slide> cachedSlide;
};

class DeleteSlideAction : public IAction {
public:
    explicit DeleteSlideAction(int index) : slideIndex(index) {}
    void execute(ISlideRepository* repository) override;
    void undo(ISlideRepository* repository) override;
    void redo(ISlideRepository* repository) override;
    std::string getName() const override { return "DeleteSlide"; }
    std::string getDescription() const override;
    bool canUndo() const override { return deletedSlide != nullptr; }

private:
    int slideIndex;
    std::unique_ptr<Slide> deletedSlide;
};

class MoveSlideAction : public IAction {
public:
    MoveSlideAction(int from, int to) : fromIndex(from), toIndex(to) {}
    void execute(ISlideRepository* repository) override;
    void undo(ISlideRepository* repository) override;
    void redo(ISlideRepository* repository) override;
    std::string getName() const override { return "MoveSlide"; }
    std::string getDescription() const override;
    bool canUndo() const override { return executed; }

private:
    int fromIndex;
    int toIndex;
    bool executed = false;
};

class AddShapeAction : public IAction {
public:
    AddShapeAction(int slideIdx, const std::string& type,
                   double x, double y, double w, double h)
        : slideIndex(slideIdx), shapeType(type), x(x), y(y), width(w), height(h) {}
    void execute(ISlideRepository* repository) override;
    void undo(ISlideRepository* repository) override;
    void redo(ISlideRepository* repository) override;
    std::string getName() const override { return "AddShape"; }
    std::string getDescription() const override;
    bool canUndo() const override { return addedShapeIndex >= 0; }

private:
    int slideIndex;
    std::string shapeType;
    double x, y, width, height;
    int addedShapeIndex = -1;
};

class RemoveShapeAction : public IAction {
public:
    RemoveShapeAction(int slideIdx, size_t shapeIdx)
        : slideIndex(slideIdx), shapeIndex(shapeIdx) {}
    void execute(ISlideRepository* repository) override;
    void undo(ISlideRepository* repository) override;
    void redo(ISlideRepository* repository) override;
    std::string getName() const override { return "RemoveShape"; }
    std::string getDescription() const override;
    bool canUndo() const override { return removedShape != nullptr; }

private:
    int slideIndex;
    size_t shapeIndex;
    std::unique_ptr<IShape> removedShape;
};

class AddTextAction : public IAction {
public:
    AddTextAction(int slideIdx, const std::string& txt)
        : slideIndex(slideIdx), newText(txt) {}
    void execute(ISlideRepository* repository) override;
    void undo(ISlideRepository* repository) override;
    void redo(ISlideRepository* repository) override;
    std::string getName() const override { return "AddText"; }
    std::string getDescription() const override;
    bool canUndo() const override { return executed; }

private:
    int slideIndex;
    std::string newText;
    bool executed = false;
};

class EditTextAction : public IAction {
public:
    EditTextAction(int slideIdx, const std::string& txt)
        : slideIndex(slideIdx), newText(txt) {}
    void execute(ISlideRepository* repository) override;
    void undo(ISlideRepository* repository) override;
    void redo(ISlideRepository* repository) override;
    std::string getName() const override { return "EditText"; }
    std::string getDescription() const override;
    bool canUndo() const override { return executed; }
    bool merge(const IAction* other) override;

private:
    int slideIndex;
    std::string newText;
    std::string previousText;
    bool executed = false;
};

class ClearTextAction : public IAction {
public:
    explicit ClearTextAction(int slideIdx) : slideIndex(slideIdx) {}
    void execute(ISlideRepository* repository) override;
    void undo(ISlideRepository* repository) override;
    void redo(ISlideRepository* repository) override;
    std::string getName() const override { return "ClearText"; }
    std::string getDescription() const override;
    bool canUndo() const override { return !clearedText.empty(); }

private:
    int slideIndex;
    std::string clearedText;
};
