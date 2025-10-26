#include "../../include/core/Shape.hpp"
#include <stdexcept>

std::unique_ptr<IShape> Shape::createShape(const std::string& shapeType) {
    if (shapeType == "Rectangle") {
        return std::make_unique<Rectangle>();
    } else if (shapeType == "Circle") {
        return std::make_unique<Circle>();
    } else if (shapeType == "Triangle") {
        return std::make_unique<Triangle>();
    }
    throw std::invalid_argument("Unknown shape type: " + shapeType);
}

std::unique_ptr<IShape> Shape::clone() const {
    return Shape::createShape(type);
}