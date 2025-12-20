#include "../../include/core/Slide.hpp"
#include <sstream>
#include <stdexcept>

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
        ss << shape->serialize() << " ";
    }
    return ss.str();
}

std::unique_ptr<IShape> Slide::removeShape(size_t index) {
    if (index >= shapes.size()) {
        throw std::out_of_range("Shape index out of range");
    }
    auto shape = std::move(shapes[index]);
    shapes.erase(shapes.begin() + static_cast<long>(index));
    return shape;
}

void Slide::insertShape(size_t index, std::unique_ptr<IShape> shape) {
    if (index > shapes.size()) {
        throw std::out_of_range("Shape index out of range");
    }
    shapes.insert(shapes.begin() + static_cast<long>(index), std::move(shape));
}

void Slide::clearShapes() {
    shapes.clear();
}

void Slide::clearText() {
    slideText.clear();
}

std::unique_ptr<Slide> Slide::clone() const {
    auto copy = std::make_unique<Slide>(slideNumber);
    copy->setText(slideText);
    for (const auto& shape : shapes) {
        copy->addShape(shape->clone());
    }
    return copy;
}