#include "../../include/core/Slide.hpp"
#include <sstream>

Slide::Slide(int number) : slideNumber(number), slideText("") {}

int Slide::getSlideNumber() const {
    return slideNumber;
}

void Slide::setSlideNumber(int number) {
    slideNumber = number;
}

void Slide::addShape(std::unique_ptr<IShape> shape) {
    shapes.push_back(std::move(shape));
}

const std::vector<std::unique_ptr<IShape>>& Slide::getShapes() const {
    return shapes;
}

void Slide::setText(const std::string& text) {
    slideText = text;
}

std::string Slide::getText() const {
    return slideText;
}

std::string Slide::serialize() const {
    std::stringstream ss;
    ss << "Slide " << slideNumber << ": ";
    if (!slideText.empty()) {
        ss << "Text[" << slideText << "] ";
    }
    ss << "Shapes: ";
    for (const auto& shape : shapes) {
        ss << shape->getType() << " ";
    }
    return ss.str();
}