#pragma once

#include "IShape.h"
#include "CPoint.h"

class CLineSegment : public IShape
{
public:
    CLineSegment(const CPoint& start, const CPoint& end, uint32_t outlineColor)
        : IShape(outlineColor)   // инициализируем m_outlineColor в IShape
        , m_start(start)
        , m_end(end)
    {}

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const;

    CPoint GetStartPoint() const;
    CPoint GetEndPoint()   const;

private:
    CPoint m_start, m_end;
};
