#include "../../include/rendering/SVGExporter.hpp"
#include "../../include/rendering/SVGRenderer.hpp"
#include "../../include/rendering/SlideRenderer.hpp"
#include <fstream>
#include <sstream>

bool SVGExporter::exportSlide(const Slide* slide, const std::string& filename) {
    std::string svg = renderToString(slide);

    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << svg;
    file.close();
    return true;
}

bool SVGExporter::exportAllSlides(ISlideRepository* repository,
                                   const std::string& directory) {
    bool allSuccess = true;

    for (int i = 0; i < repository->getSlideCount(); ++i) {
        Slide* slide = repository->getSlide(i);
        std::stringstream filename;
        filename << directory << "/slide" << (i + 1) << ".svg";

        if (!exportSlide(slide, filename.str())) {
            allSuccess = false;
        }
    }

    return allSuccess;
}

std::string SVGExporter::renderToString(const Slide* slide) {
    SVGRenderer renderer;
    SlideRenderer slideRenderer;
    slideRenderer.render(slide, &renderer);
    return renderer.getOutput();
}
