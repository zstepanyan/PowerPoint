#include "../../include/rendering/SVGRenderer.hpp"

void SVGRenderer::beginDocument(double width, double height) {
    buffer.str("");
    buffer << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    buffer << "<svg xmlns=\"http://www.w3.org/2000/svg\" ";
    buffer << "width=\"" << width << "\" height=\"" << height << "\" ";
    buffer << "viewBox=\"0 0 " << width << " " << height << "\">\n";
    buffer << "  <rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
}

void SVGRenderer::endDocument() {
    buffer << "</svg>\n";
}

std::string SVGRenderer::getOutput() const {
    return buffer.str();
}

void SVGRenderer::drawRectangle(double x, double y, double width, double height,
                                 const RenderStyle& style) {
    buffer << "  <rect x=\"" << x << "\" y=\"" << y
           << "\" width=\"" << width << "\" height=\"" << height
           << "\" " << formatStyle(style) << "/>\n";
}

void SVGRenderer::drawCircle(double cx, double cy, double radius,
                              const RenderStyle& style) {
    buffer << "  <circle cx=\"" << cx << "\" cy=\"" << cy
           << "\" r=\"" << radius
           << "\" " << formatStyle(style) << "/>\n";
}

void SVGRenderer::drawTriangle(double x1, double y1, double x2, double y2,
                                double x3, double y3, const RenderStyle& style) {
    buffer << "  <polygon points=\"" << x1 << "," << y1
           << " " << x2 << "," << y2
           << " " << x3 << "," << y3
           << "\" " << formatStyle(style) << "/>\n";
}

void SVGRenderer::drawText(double x, double y, const std::string& text,
                            const RenderStyle& style) {
    buffer << "  <text x=\"" << x << "\" y=\"" << y
           << "\" font-family=\"" << style.fontFamily
           << "\" font-size=\"" << style.fontSize
           << "\" fill=\"" << style.fillColor << "\">"
           << escapeXml(text) << "</text>\n";
}

std::string SVGRenderer::formatStyle(const RenderStyle& style) const {
    std::stringstream ss;
    ss << "fill=\"" << style.fillColor << "\" "
       << "stroke=\"" << style.strokeColor << "\" "
       << "stroke-width=\"" << style.strokeWidth << "\" "
       << "opacity=\"" << style.opacity << "\"";
    return ss.str();
}

std::string SVGRenderer::escapeXml(const std::string& text) const {
    std::string result;
    result.reserve(text.size());
    for (char c : text) {
        switch (c) {
            case '&':  result += "&amp;";  break;
            case '<':  result += "&lt;";   break;
            case '>':  result += "&gt;";   break;
            case '"':  result += "&quot;"; break;
            case '\'': result += "&apos;"; break;
            default:   result += c;        break;
        }
    }
    return result;
}
