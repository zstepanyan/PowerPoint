#include "../../include/core/Shape.hpp"
#include <stdexcept>
#include <sstream>

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

std::unique_ptr<IShape> Shape::createShape(const std::string& shapeType,
                                            double x, double y,
                                            double width, double height) {
    if (shapeType == "Rectangle") {
        return std::make_unique<Rectangle>(x, y, width, height);
    } else if (shapeType == "Circle") {
        return std::make_unique<Circle>(x, y, width, height);
    } else if (shapeType == "Triangle") {
        return std::make_unique<Triangle>(x, y, width, height);
    }
    throw std::invalid_argument("Unknown shape type: " + shapeType);
}

std::unique_ptr<IShape> Shape::clone() const {
    auto copy = Shape::createShape(type);
    copy->setPosition(x, y);
    copy->setDimensions(width, height);
    return copy;
}

std::string Shape::serialize() const {
    std::stringstream ss;
    ss << type << " (" << x << ", " << y << ") " << width << "x" << height;
    return ss.str();
}