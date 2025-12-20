#pragma once
#include "../interfaces/ISlideRepository.hpp"
#include "../core/Slide.hpp"
#include <string>

class SVGExporter {
public:
    // Export single slide to SVG file
    static bool exportSlide(const Slide* slide, const std::string& filename);

    // Export all slides to SVG files (slide1.svg, slide2.svg, etc.)
    static bool exportAllSlides(ISlideRepository* repository,
                                const std::string& directory);

    // Get SVG string without writing to file (for preview)
    static std::string renderToString(const Slide* slide);
};
