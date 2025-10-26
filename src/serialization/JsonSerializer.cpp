#include "../../include/serialization/JsonSerializer.hpp"
#include "../../include/interfaces/ISlideRepository.hpp"
#include "../../include/core/Slide.hpp"
#include "../../include/core/Shape.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

std::string JsonSerializer::serialize(ISlideRepository* repository) const {
    json root;
    root["version"] = "1.0";
    root["slides"] = json::array();
    
    for (int i = 0; i < repository->getSlideCount(); ++i) {
        Slide* slide = repository->getSlide(i);
        json slideObj;
        slideObj["number"] = slide->getSlideNumber();
        slideObj["text"] = slide->getText();
        slideObj["shapes"] = json::array();
        
        for (const auto& shape : slide->getShapes()) {
            slideObj["shapes"].push_back(shape->getType());
        }
        
        root["slides"].push_back(slideObj);
    }
    
    return root.dump(2);
}

void JsonSerializer::deserialize(const std::string& data, ISlideRepository* repository) {
    try {
        json root = json::parse(data);
        
        auto& slides = repository->getSlides();
        slides.clear();
        
        for (const auto& slideJson : root["slides"]) {
            int number = slideJson["number"];
            auto slide = std::make_unique<Slide>(number);
            
            std::string text = slideJson.value("text", "");
            slide->setText(text);
            
            if (slideJson.contains("shapes")) {
                for (const auto& shapeType : slideJson["shapes"]) {
                    auto shape = Shape::createShape(shapeType);
                    slide->addShape(std::move(shape));
                }
            }
            
            slides.push_back(std::move(slide));
        }
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Deserialization error: ") + e.what());
    }
}

