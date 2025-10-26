#include "../../include/commands/Commands.hpp"
#include "../../include/core/Slide.hpp"
#include "../../include/core/SlideFactory.hpp"
#include "../../include/core/Shape.hpp"
#include "../../include/serialization/JsonSerializer.hpp"
#include <iostream>
#include <fstream>

void CreateSlideCommand::execute(ISlideRepository* repository) {
    auto slide = SlideFactory::createSlide(repository->getSlideCount() + 1);
    repository->addSlide(std::move(slide));
    std::cout << "Slide " << slideNumber << " created.\n";
}

void MoveSlideCommand::execute(ISlideRepository* repository) {
    try {
        repository->moveSlide(fromIndex - 1, toIndex - 1);
        std::cout << "Slide moved from position " << fromIndex 
                  << " to " << toIndex << ".\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void AddShapeCommand::execute(ISlideRepository* repository) {
    try {
        Slide* slide = repository->getSlide(slideIndex - 1);
        auto shape = Shape::createShape(shapeType);
        slide->addShape(std::move(shape));
        std::cout << "Shape " << shapeType << " added to slide " 
                  << slideIndex << ".\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void AddTextCommand::execute(ISlideRepository* repository) {
    try {
        Slide* slide = repository->getSlide(slideIndex - 1);
        slide->setText(text);
        std::cout << "Text added to slide " << slideIndex << ".\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void ListSlidesCommand::execute(ISlideRepository* repository) {
    if (repository->getSlideCount() == 0) {
        std::cout << "No slides available.\n";
        return;
    }
    
    std::cout << "--- Slides ---\n";
    for (int i = 0; i < repository->getSlideCount(); ++i) {
        Slide* slide = repository->getSlide(i);
        std::cout << slide->serialize() << "\n";
    }
}

void DisplaySlideCommand::execute(ISlideRepository* repository) {
    try {
        Slide* slide = repository->getSlide(slideIndex - 1);
        std::cout << "\n=== " << slide->serialize() << " ===\n";
        if (!slide->getText().empty()) {
            std::cout << "Text: " << slide->getText() << "\n";
        }
        std::cout << "Shapes: ";
        for (const auto& shape : slide->getShapes()) {
            std::cout << shape->getType() << " ";
        }
        std::cout << "\n\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void SaveCommand::execute(ISlideRepository* repository) {
    try {
        JsonSerializer serializer;
        std::string data = serializer.serialize(repository);
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        file << data;
        file.close();
        std::cout << "Presentation saved to " << filename << ".\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void LoadCommand::execute(ISlideRepository* repository) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        
        std::string data((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
        file.close();
        
        JsonSerializer serializer;
        serializer.deserialize(data, repository);
        std::cout << "Presentation loaded from " << filename << ".\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void ExitCommand::execute(ISlideRepository* repository) {
    std::cout << "Exiting SlideEditor.\n";
}