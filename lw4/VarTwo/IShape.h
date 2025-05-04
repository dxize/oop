#pragma once
#include <string>
#include <cstdint>
#include "./DrawShapes/ICanvasDrawable.h"

class IShape: public ICanvasDrawable
{
public:
    explicit IShape(uint32_t outlineColor)
        : m_outlineColor(outlineColor)
    {}

    virtual ~IShape() = default;
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual std::string ToString() const = 0;
    virtual uint32_t GetOutlineColor() const = 0;

protected:
    uint32_t m_outlineColor;
};
