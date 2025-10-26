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
    AddShapeCommand(int idx, const std::string& type) 
        : slideIndex(idx), shapeType(type) {}
    void execute(ISlideRepository* repository) override;
    std::string getName() const override { return "AddShape"; }

private:
    int slideIndex;
    std::string shapeType;

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