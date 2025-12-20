#include "../../include/core/SlideRepository.hpp"
#include <stdexcept>
#include <algorithm>

void SlideRepository::addSlide(std::unique_ptr<Slide> slide) {
    slides.push_back(std::move(slide));
}

Slide* SlideRepository::getSlide(int index) {
    if (index < 0 || index >= static_cast<int>(slides.size())) {
        throw std::out_of_range("Slide index out of range");
    }
    return slides[index].get();
}

int SlideRepository::getSlideCount() const {
    return slides.size();
}

void SlideRepository::moveSlide(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= static_cast<int>(slides.size()) ||
        toIndex < 0 || toIndex >= static_cast<int>(slides.size())) {
        throw std::out_of_range("Invalid slide indices for move");
    }
    
    if (fromIndex == toIndex) return;
    
    auto slide = std::move(slides[fromIndex]);
    slides.erase(slides.begin() + fromIndex);
    
    if (toIndex > fromIndex) {
        toIndex--;
    }
    
    slides.insert(slides.begin() + toIndex, std::move(slide));
    
    // Update slide numbers
    for (int i = 0; i < static_cast<int>(slides.size()); ++i) {
        slides[i]->setSlideNumber(i + 1);
    }
}

std::vector<std::unique_ptr<Slide>>& SlideRepository::getSlides() {
    return slides;
}