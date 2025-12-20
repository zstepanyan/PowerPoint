#pragma once
#include <string>
#include <memory>

class IShape {
public:
    virtual ~IShape() = default;
    virtual std::string getType() const = 0;
    virtual std::string serialize() const = 0;
    virtual std::unique_ptr<IShape> clone() const = 0;

    // Position and dimension methods
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual double getWidth() const = 0;
    virtual double getHeight() const = 0;
    virtual void setDimensions(double width, double height) = 0;
};