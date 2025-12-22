#pragma once
#include <string>

struct RenderStyle {
    std::string fillColor = "white";
    std::string strokeColor = "black";
    double strokeWidth = 1.0;
    double opacity = 1.0;
    std::string fontFamily = "Arial";
    int fontSize = 14;
};

class IRenderer {
public:
    virtual ~IRenderer() = default;

    // Document control
    virtual void beginDocument(double width, double height) = 0;
    virtual void endDocument() = 0;
    virtual std::string getOutput() const = 0;

    // Drawing primitives
    virtual void drawRectangle(double x, double y, double width, double height,
                               const RenderStyle& style) = 0;
    virtual void drawCircle(double cx, double cy, double radius,
                            const RenderStyle& style) = 0;
    virtual void drawTriangle(double x1, double y1, double x2, double y2,
                              double x3, double y3, const RenderStyle& style) = 0;
    virtual void drawText(double x, double y, const std::string& text,
                          const RenderStyle& style) = 0;
};
