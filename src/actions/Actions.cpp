#include "../../include/actions/Actions.hpp"
#include "../../include/core/Shape.hpp"
#include "../../include/core/SlideFactory.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

// ============================================================================
// CreateSlideAction
// ============================================================================

void CreateSlideAction::execute(ISlideRepository* repository) {
    createdIndex = repository->getSlideCount();
    auto slide = SlideFactory::createSlide(createdIndex + 1);
    repository->addSlide(std::move(slide));
    std::cout << "Slide " << (createdIndex + 1) << " created.\n";
}

void CreateSlideAction::undo(ISlideRepository* repository) {
    if (createdIndex < 0 || createdIndex >= repository->getSlideCount()) {
        return;
    }
    // Cache the slide for potential redo
    auto& slides = repository->getSlides();
    cachedSlide = std::move(slides[static_cast<size_t>(createdIndex)]);
    slides.erase(slides.begin() + createdIndex);

    // Update slide numbers
    for (int i = createdIndex; i < repository->getSlideCount(); ++i) {
        repository->getSlide(i)->setSlideNumber(i + 1);
    }
}

void CreateSlideAction::redo(ISlideRepository* repository) {
    if (cachedSlide) {
        auto& slides = repository->getSlides();
        slides.insert(slides.begin() + createdIndex, std::move(cachedSlide));

        // Update slide numbers
        for (int i = createdIndex; i < repository->getSlideCount(); ++i) {
            repository->getSlide(i)->setSlideNumber(i + 1);
        }
        std::cout << "Slide " << (createdIndex + 1) << " created.\n";
    } else {
        execute(repository);
    }
}

std::string CreateSlideAction::getDescription() const {
    std::stringstream ss;
    ss << "Create slide " << (createdIndex + 1);
    return ss.str();
}

// ============================================================================
// DeleteSlideAction
// ============================================================================

void DeleteSlideAction::execute(ISlideRepository* repository) {
    if (slideIndex < 0 || slideIndex >= repository->getSlideCount()) {
        throw std::out_of_range("Slide index out of range");
    }

    auto& slides = repository->getSlides();
    deletedSlide = std::move(slides[static_cast<size_t>(slideIndex)]);
    slides.erase(slides.begin() + slideIndex);

    // Update slide numbers
    for (int i = slideIndex; i < repository->getSlideCount(); ++i) {
        repository->getSlide(i)->setSlideNumber(i + 1);
    }

    std::cout << "Slide " << (slideIndex + 1) << " deleted.\n";
}

void DeleteSlideAction::undo(ISlideRepository* repository) {
    if (!deletedSlide) return;

    auto& slides = repository->getSlides();
    slides.insert(slides.begin() + slideIndex, std::move(deletedSlide));

    // Update slide numbers
    for (int i = slideIndex; i < repository->getSlideCount(); ++i) {
        repository->getSlide(i)->setSlideNumber(i + 1);
    }
}

void DeleteSlideAction::redo(ISlideRepository* repository) {
    execute(repository);
}

std::string DeleteSlideAction::getDescription() const {
    std::stringstream ss;
    ss << "Delete slide " << (slideIndex + 1);
    return ss.str();
}

// ============================================================================
// MoveSlideAction
// ============================================================================

void MoveSlideAction::execute(ISlideRepository* repository) {
    repository->moveSlide(fromIndex, toIndex);
    executed = true;
    std::cout << "Slide moved from position " << (fromIndex + 1)
              << " to " << (toIndex + 1) << ".\n";
}

void MoveSlideAction::undo(ISlideRepository* repository) {
    // Reverse the move
    repository->moveSlide(toIndex, fromIndex);
}

void MoveSlideAction::redo(ISlideRepository* repository) {
    repository->moveSlide(fromIndex, toIndex);
    std::cout << "Slide moved from position " << (fromIndex + 1)
              << " to " << (toIndex + 1) << ".\n";
}

std::string MoveSlideAction::getDescription() const {
    std::stringstream ss;
    ss << "Move slide from " << (fromIndex + 1) << " to " << (toIndex + 1);
    return ss.str();
}

// ============================================================================
// AddShapeAction
// ============================================================================

void AddShapeAction::execute(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    auto shape = Shape::createShape(shapeType, x, y, width, height);
    slide->addShape(std::move(shape));
    addedShapeIndex = static_cast<int>(slide->getShapes().size()) - 1;

    std::cout << "Shape " << shapeType << " added to slide "
              << (slideIndex + 1) << " at (" << x << ", " << y
              << ") size " << width << "x" << height << ".\n";
}

void AddShapeAction::undo(ISlideRepository* repository) {
    if (addedShapeIndex < 0) return;

    Slide* slide = repository->getSlide(slideIndex);
    slide->removeShape(static_cast<size_t>(addedShapeIndex));
}

void AddShapeAction::redo(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    auto shape = Shape::createShape(shapeType, x, y, width, height);
    slide->addShape(std::move(shape));
    addedShapeIndex = static_cast<int>(slide->getShapes().size()) - 1;

    std::cout << "Shape " << shapeType << " added to slide "
              << (slideIndex + 1) << " at (" << x << ", " << y
              << ") size " << width << "x" << height << ".\n";
}

std::string AddShapeAction::getDescription() const {
    std::stringstream ss;
    ss << "Add " << shapeType << " to slide " << (slideIndex + 1);
    return ss.str();
}

// ============================================================================
// RemoveShapeAction
// ============================================================================

void RemoveShapeAction::execute(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    removedShape = slide->removeShape(shapeIndex);

    std::cout << "Shape " << removedShape->getType() << " removed from slide "
              << (slideIndex + 1) << ".\n";
}

void RemoveShapeAction::undo(ISlideRepository* repository) {
    if (!removedShape) return;

    Slide* slide = repository->getSlide(slideIndex);
    slide->insertShape(shapeIndex, std::move(removedShape));
}

void RemoveShapeAction::redo(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    removedShape = slide->removeShape(shapeIndex);

    std::cout << "Shape " << removedShape->getType() << " removed from slide "
              << (slideIndex + 1) << ".\n";
}

std::string RemoveShapeAction::getDescription() const {
    std::stringstream ss;
    ss << "Remove shape " << (shapeIndex + 1) << " from slide " << (slideIndex + 1);
    return ss.str();
}

// ============================================================================
// AddTextAction
// ============================================================================

void AddTextAction::execute(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);

    if (!slide->getText().empty()) {
        throw std::runtime_error("Slide already has text. Use edittext to modify.");
    }

    slide->setText(newText);
    executed = true;
    std::cout << "Text added to slide " << (slideIndex + 1) << ".\n";
}

void AddTextAction::undo(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    slide->clearText();
}

void AddTextAction::redo(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    slide->setText(newText);
    std::cout << "Text added to slide " << (slideIndex + 1) << ".\n";
}

std::string AddTextAction::getDescription() const {
    std::stringstream ss;
    ss << "Add text \"" << newText.substr(0, 20);
    if (newText.length() > 20) ss << "...";
    ss << "\" to slide " << (slideIndex + 1);
    return ss.str();
}

// ============================================================================
// EditTextAction
// ============================================================================

void EditTextAction::execute(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    previousText = slide->getText();
    slide->setText(newText);
    executed = true;
    std::cout << "Text updated on slide " << (slideIndex + 1) << ".\n";
}

void EditTextAction::undo(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    slide->setText(previousText);
}

void EditTextAction::redo(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    slide->setText(newText);
    std::cout << "Text updated on slide " << (slideIndex + 1) << ".\n";
}

std::string EditTextAction::getDescription() const {
    std::stringstream ss;
    ss << "Edit text on slide " << (slideIndex + 1);
    return ss.str();
}

bool EditTextAction::merge(const IAction* other) {
    const EditTextAction* otherEdit = dynamic_cast<const EditTextAction*>(other);
    if (otherEdit && otherEdit->slideIndex == slideIndex) {
        // Merge by keeping original previousText and using new newText
        newText = otherEdit->newText;
        return true;
    }
    return false;
}

// ============================================================================
// ClearTextAction
// ============================================================================

void ClearTextAction::execute(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    clearedText = slide->getText();

    if (clearedText.empty()) {
        std::cout << "Slide " << (slideIndex + 1) << " has no text to clear.\n";
        return;
    }

    slide->clearText();
    std::cout << "Text cleared from slide " << (slideIndex + 1) << ".\n";
}

void ClearTextAction::undo(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    slide->setText(clearedText);
}

void ClearTextAction::redo(ISlideRepository* repository) {
    Slide* slide = repository->getSlide(slideIndex);
    slide->clearText();
    std::cout << "Text cleared from slide " << (slideIndex + 1) << ".\n";
}

std::string ClearTextAction::getDescription() const {
    std::stringstream ss;
    ss << "Clear text from slide " << (slideIndex + 1);
    return ss.str();
}
