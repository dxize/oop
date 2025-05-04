#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include <string>
#include <cstdint>

class CRectangle : public ISolidShape
{
public:
    CRectangle(const CPoint& topLeft, const CPoint& bottomRight,
               uint32_t outlineColor, uint32_t fillColor)
        : m_leftTop(topLeft)
        , m_rightBottom(bottomRight)
        , ISolidShape(outlineColor, fillColor)
    {}

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;

    void Draw(ICanvas& canvas) const override;

    CPoint GetLeftTop() const;
    CPoint GetRightBottom() const;
    double GetWidth() const;
    double GetHeight() const;

private:
    CPoint   m_leftTop;
    CPoint   m_rightBottom;
};
