#pragma once
#include "../interfaces/IShape.hpp"
#include <memory>
#include <map>
#include <sstream>

class Shape : public IShape {
public:
    std::string getType() const override { return type; }
    std::string serialize() const override;
    std::unique_ptr<IShape> clone() const override;

    // Position and dimension implementations
    double getX() const override { return x; }
    double getY() const override { return y; }
    void setPosition(double newX, double newY) override { x = newX; y = newY; }
    double getWidth() const override { return width; }
    double getHeight() const override { return height; }
    void setDimensions(double w, double h) override { width = w; height = h; }

    static std::unique_ptr<IShape> createShape(const std::string& shapeType);
    static std::unique_ptr<IShape> createShape(const std::string& shapeType,
                                                double x, double y,
                                                double width, double height);

protected:
    std::string type;
    double x = 0.0;
    double y = 0.0;
    double width = 100.0;
    double height = 100.0;

    Shape(const std::string& t) : type(t) {}
    Shape(const std::string& t, double x, double y, double w, double h)
        : type(t), x(x), y(y), width(w), height(h) {}
};

class Rectangle : public Shape {
public:
    Rectangle() : Shape("Rectangle") {}
    Rectangle(double x, double y, double w, double h) : Shape("Rectangle", x, y, w, h) {}
    std::unique_ptr<IShape> clone() const override {
        auto copy = std::make_unique<Rectangle>();
        copy->setPosition(x, y);
        copy->setDimensions(width, height);
        return copy;
    }
};

class Circle : public Shape {
public:
    Circle() : Shape("Circle") {}
    Circle(double x, double y, double w, double h) : Shape("Circle", x, y, w, h) {}
    std::unique_ptr<IShape> clone() const override {
        auto copy = std::make_unique<Circle>();
        copy->setPosition(x, y);
        copy->setDimensions(width, height);
        return copy;
    }
};

class Triangle : public Shape {
public:
    Triangle() : Shape("Triangle") {}
    Triangle(double x, double y, double w, double h) : Shape("Triangle", x, y, w, h) {}
    std::unique_ptr<IShape> clone() const override {
        auto copy = std::make_unique<Triangle>();
        copy->setPosition(x, y);
        copy->setDimensions(width, height);
        return copy;
    }
};