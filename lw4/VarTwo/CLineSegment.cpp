#include "CLineSegment.h"
#include <cmath>
#include <sstream>
#include <iomanip>


double CLineSegment::GetArea() const
{
    return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	double result = sqrt(pow(m_end.x - m_start.x, 2) + pow(m_end.y - m_start.y, 2));
	return result;
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_start;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_end;
}

std::string CLineSegment::ToString() const {
    std::ostringstream ss;
    ss << "Line Segment:\n"
        << "  Start point: (" << m_start.x << ", " << m_start.y << ")\n"
        << "  End point: (" << m_end.x << ", " << m_end.y << ")\n"
        << "  Length: " << GetPerimeter() << "\n"
        << "  Outline color: #"
        << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor;
    return ss.str();
}

void CLineSegment::Draw(ICanvas& canvas) const
{
    canvas.DrawLine(m_start, m_end, m_outlineColor);
}