#pragma once
#include "../interfaces/ICommand.hpp"
#include "../interfaces/ISlideRepository.hpp"
#include <string>
#include <memory>

class CreateSlideCommand : public ICommand {
public:
    CreateSlideCommand(int num) : slideNumber(num) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "CreateSlide"; }

private:
    int slideNumber;
};

class MoveSlideCommand : public ICommand {
public:
    MoveSlideCommand(int from, int to) : fromIndex(from), toIndex(to) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "MoveSlide"; }

private:
    int fromIndex;
    int toIndex;
};

class AddShapeCommand : public ICommand {
public:
    AddShapeCommand(int idx, const std::string& type,
                    double x, double y, double w, double h)
        : slideIndex(idx), shapeType(type), x(x), y(y), width(w), height(h) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "AddShape"; }

private:
    int slideIndex;
    std::string shapeType;
    double x, y, width, height;
};

class AddTextCommand : public ICommand {
public:
    AddTextCommand(int idx, const std::string& txt) 
        : slideIndex(idx), text(txt) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "AddText"; }
private:
    int slideIndex;
    std::string text;
};

class ListSlidesCommand : public ICommand {
public:
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "ListSlides"; }
};

class DisplaySlideCommand : public ICommand {
public:
    DisplaySlideCommand(int idx) : slideIndex(idx) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "DisplaySlide"; }
private:
    int slideIndex;
};

class SaveCommand : public ICommand {
public:
    SaveCommand(const std::string& fname) : filename(fname) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "Save"; }
private:
    std::string filename;
};

class LoadCommand : public ICommand {
public:
    LoadCommand(const std::string& fname) : filename(fname) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "Load"; }
private:
    std::string filename;
};

class ExitCommand : public ICommand {
public:
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "Exit"; }
};

// New commands for undo/redo functionality

class DeleteSlideCommand : public ICommand {
public:
    explicit DeleteSlideCommand(int idx) : slideIndex(idx) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "DeleteSlide"; }
private:
    int slideIndex;
};

class RemoveShapeCommand : public ICommand {
public:
    RemoveShapeCommand(int slideIdx, size_t shapeIdx)
        : slideIndex(slideIdx), shapeIndex(shapeIdx) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "RemoveShape"; }
private:
    int slideIndex;
    size_t shapeIndex;
};

class EditTextCommand : public ICommand {
public:
    EditTextCommand(int idx, const std::string& txt)
        : slideIndex(idx), text(txt) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "EditText"; }
private:
    int slideIndex;
    std::string text;
};

class ClearTextCommand : public ICommand {
public:
    explicit ClearTextCommand(int idx) : slideIndex(idx) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "ClearText"; }
private:
    int slideIndex;
};

class UndoCommand : public ICommand {
public:
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "Undo"; }
};

class RedoCommand : public ICommand {
public:
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "Redo"; }
};

class HistoryCommand : public ICommand {
public:
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "History"; }
};

class SetHistoryCommand : public ICommand {
public:
    explicit SetHistoryCommand(size_t size) : historySize(size) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "SetHistory"; }
private:
    size_t historySize;
};

// SVG Export commands

class ExportCommand : public ICommand {
public:
    ExportCommand(int slideIdx, const std::string& fname)
        : slideIndex(slideIdx), filename(fname) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "Export"; }
private:
    int slideIndex;
    std::string filename;
};

class ExportAllCommand : public ICommand {
public:
    explicit ExportAllCommand(const std::string& dir) : directory(dir) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "ExportAll"; }
private:
    std::string directory;
};

class PreviewCommand : public ICommand {
public:
    explicit PreviewCommand(int slideIdx) : slideIndex(slideIdx) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "Preview"; }
private:
    int slideIndex;
};