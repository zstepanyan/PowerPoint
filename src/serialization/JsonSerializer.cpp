#include "../../include/serialization/JsonSerializer.hpp"
#include "../../include/interfaces/ISlideRepository.hpp"
#include "../../include/core/Slide.hpp"
#include "../../include/core/Shape.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

std::string JsonSerializer::serialize(ISlideRepository* repository) const {
    json root;
    root["version"] = "2.0";
    root["slides"] = json::array();

    for (int i = 0; i < repository->getSlideCount(); ++i) {
        Slide* slide = repository->getSlide(i);
        json slideObj;
        slideObj["number"] = slide->getSlideNumber();
        slideObj["text"] = slide->getText();
        slideObj["shapes"] = json::array();

        for (const auto& shape : slide->getShapes()) {
            json shapeObj;
            shapeObj["type"] = shape->getType();
            shapeObj["x"] = shape->getX();
            shapeObj["y"] = shape->getY();
            shapeObj["width"] = shape->getWidth();
            shapeObj["height"] = shape->getHeight();
            slideObj["shapes"].push_back(shapeObj);
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
                for (const auto& shapeData : slideJson["shapes"]) {
                    std::unique_ptr<IShape> shape;

                    if (shapeData.is_string()) {
                        shape = Shape::createShape(shapeData.get<std::string>());
                    } else {
                        std::string shapeType = shapeData["type"];
                        double x = shapeData.value("x", 0.0);
                        double y = shapeData.value("y", 0.0);
                        double width = shapeData.value("width", 100.0);
                        double height = shapeData.value("height", 100.0);
                        shape = Shape::createShape(shapeType, x, y, width, height);
                    }

                    slide->addShape(std::move(shape));
                }
            }

            slides.push_back(std::move(slide));
        }
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Deserialization error: ") + e.what());
    }
}
