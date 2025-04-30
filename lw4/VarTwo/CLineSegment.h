#pragma once
#include "IShape.h"
#include <string>
#include <cstdint>
#include "CPoint.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& start, const CPoint& end, uint32_t color)
		: m_start(start), m_end(end), m_outlineColor(color) {}

	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	CPoint GetStartPoint();
	CPoint GetEndPoint();
private:
	CPoint m_start, m_end;
	uint32_t m_outlineColor;
};
