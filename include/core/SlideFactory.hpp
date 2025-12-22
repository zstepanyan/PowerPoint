#pragma once
#include "Slide.hpp"
#include <memory>

class SlideFactory {
public:
    static std::unique_ptr<Slide> createSlide(int slideNumber);
};