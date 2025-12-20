#pragma once
#include "../core/Slide.hpp"
#include "../interfaces/IRenderer.hpp"

class SlideRenderer {
public:
    static constexpr double SLIDE_WIDTH = 800.0;
    static constexpr double SLIDE_HEIGHT = 600.0;

    void render(const Slide* slide, IRenderer* renderer) const;
};
