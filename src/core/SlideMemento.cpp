#include "../../include/core/SlideMemento.hpp"

std::unique_ptr<SlideMemento> SlideMemento::capture(const Slide* slide) {
    auto memento = std::unique_ptr<SlideMemento>(new SlideMemento());
    memento->slideNumber = slide->getSlideNumber();
    memento->text = slide->getText();

    // Deep copy all shapes using clone()
    for (const auto& shape : slide->getShapes()) {
        memento->shapes.push_back(shape->clone());
    }

    return memento;
}

void SlideMemento::restore(Slide* slide) const {
    slide->setSlideNumber(slideNumber);
    slide->setText(text);
    slide->clearShapes();

    // Deep copy shapes back to slide
    for (const auto& shape : shapes) {
        slide->addShape(shape->clone());
    }
}
