#pragma once
#include "Slide.hpp"
#include "../interfaces/IShape.hpp"
#include <memory>
#include <vector>
#include <string>

class SlideMemento {
public:
    // Capture entire slide state
    static std::unique_ptr<SlideMemento> capture(const Slide* slide);

    // Restore slide from memento
    void restore(Slide* slide) const;

    // Getters for accessing captured state
    int getSlideNumber() const { return slideNumber; }
    const std::string& getText() const { return text; }
    const std::vector<std::unique_ptr<IShape>>& getShapes() const { return shapes; }

private:
    SlideMemento() = default;

    int slideNumber = 0;
    std::string text;
    std::vector<std::unique_ptr<IShape>> shapes;
};
