#include "../../include/rendering/SlideRenderer.hpp"
#include "../../include/interfaces/IRenderer.hpp"
#include <algorithm>

void SlideRenderer::render(const Slide* slide, IRenderer* renderer) const {
    renderer->beginDocument(SLIDE_WIDTH, SLIDE_HEIGHT);

    // Draw slide text at top
    if (!slide->getText().empty()) {
        RenderStyle textStyle;
        textStyle.fillColor = "black";
        textStyle.fontFamily = "Arial";
        textStyle.fontSize = 24;
        renderer->drawText(40, 50, slide->getText(), textStyle);
    }

    // Draw all shapes
    for (const auto& shape : slide->getShapes()) {
        std::string type = shape->getType();
        double x = shape->getX();
        double y = shape->getY();
        double w = shape->getWidth();
        double h = shape->getHeight();

        RenderStyle style;
        style.strokeColor = "black";
        style.strokeWidth = 2.0;

        if (type == "Rectangle") {
            style.fillColor = "#4A90D9";
            renderer->drawRectangle(x, y, w, h, style);
        }
        else if (type == "Circle") {
            style.fillColor = "#E74C3C";
            double radius = std::min(w, h) / 2;
            renderer->drawCircle(x + w/2, y + h/2, radius, style);
        }
        else if (type == "Triangle") {
            style.fillColor = "#2ECC71";
            renderer->drawTriangle(
                x + w/2, y,           // top
                x, y + h,             // bottom-left
                x + w, y + h,         // bottom-right
                style
            );
        }
    }

    renderer->endDocument();
}
