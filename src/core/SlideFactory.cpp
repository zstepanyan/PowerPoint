#include "../../include/core/SlideFactory.hpp"

std::unique_ptr<Slide> SlideFactory::createSlide(int slideNumber) {
    return std::make_unique<Slide>(slideNumber);
}