#pragma once
#include "../interfaces/IShape.hpp"
#include <memory>
#include <map>

class Shape : public IShape {
public:
    std::string getType() const override { return type; }
    std::string serialize() const override { return type; }
    std::unique_ptr<IShape> clone() const override;
    
    static std::unique_ptr<IShape> createShape(const std::string& shapeType);

protected:
    std::string type;
    Shape(const std::string& t) : type(t) {}
};

class Rectangle : public Shape {
public:
    Rectangle() : Shape("Rectangle") {}
    std::unique_ptr<IShape> clone() const override {
        return std::make_unique<Rectangle>();
    }
};

class Circle : public Shape {
public:
    Circle() : Shape("Circle") {}
    std::unique_ptr<IShape> clone() const override {
        return std::make_unique<Circle>();
    }
};

class Triangle : public Shape {
public:
    Triangle() : Shape("Triangle") {}
    std::unique_ptr<IShape> clone() const override {
        return std::make_unique<Triangle>();
    }
};