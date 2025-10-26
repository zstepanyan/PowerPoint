// include/core/Slide.hpp
#pragma once
#include "../interfaces/IShape.hpp"
#include <vector>
#include <memory>
#include <string>

class Slide {    
public:
    Slide(int number);
    
    int getSlideNumber() const;
    void setSlideNumber(int number);
    
    void addShape(std::unique_ptr<IShape> shape);
    const std::vector<std::unique_ptr<IShape>>& getShapes() const;
    
    void setText(const std::string& text);
    std::string getText() const;
    
    std::string serialize() const;
    static std::unique_ptr<Slide> deserialize(const std::string& data);
    
private:
    int slideNumber;
    std::vector<std::unique_ptr<IShape>> shapes;
    std::string slideText;
};