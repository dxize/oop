#pragma once
#include "IShape.h"
#include <cstdint>
#include <string>

class ISolidShape : public IShape
{
public:
    ISolidShape(uint32_t outlineColor, uint32_t fillColor)
        : IShape(outlineColor)    
        , m_fillColor(fillColor)  
    {}

    ~ISolidShape() = default;
    virtual uint32_t GetFillColor() const = 0;

protected:
    uint32_t m_fillColor;
};
