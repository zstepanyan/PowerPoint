#pragma once
#include "../interfaces/IRenderer.hpp"
#include <sstream>
#include <string>

class SVGRenderer : public IRenderer {
public:
    void beginDocument(double width, double height) override;
    void endDocument() override;
    std::string getOutput() const override;

    void drawRectangle(double x, double y, double width, double height,
                       const RenderStyle& style) override;
    void drawCircle(double cx, double cy, double radius,
                    const RenderStyle& style) override;
    void drawTriangle(double x1, double y1, double x2, double y2,
                      double x3, double y3, const RenderStyle& style) override;
    void drawText(double x, double y, const std::string& text,
                  const RenderStyle& style) override;

private:
    std::stringstream buffer;
    std::string formatStyle(const RenderStyle& style) const;
    std::string escapeXml(const std::string& text) const;
};
