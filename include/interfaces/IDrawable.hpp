#pragma once

class IRenderer;

class IDrawable {
public:
    virtual ~IDrawable() = default;
    virtual void draw(IRenderer* renderer) const = 0;
};
