#pragma once
#include <string>
#include <memory>

class IShape {
public:
    virtual ~IShape() = default;
    virtual std::string getType() const = 0;
    virtual std::string serialize() const = 0;
    virtual std::unique_ptr<IShape> clone() const = 0;
};