#include "CRectangle.h"
#include <sstream>
#include <iomanip>
#include <cmath>

double CRectangle::GetArea() const
{
    return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
    return 2.0 * (GetWidth() + GetHeight());
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
    return m_rightBottom;
}

double CRectangle::GetWidth() const
{
    return std::abs(m_rightBottom.x - m_leftTop.x);
}

double CRectangle::GetHeight() const
{
    return std::abs(m_rightBottom.y - m_leftTop.y);
}

std::string CRectangle::ToString() const
{
    std::ostringstream ss;
    ss << "Rectangle:\n"
        << "  Top-left: (" << m_leftTop.x << ", " << m_leftTop.y << ")\n"
        << "  Bottom-right: (" << m_rightBottom.x << ", " << m_rightBottom.y << ")\n"
        << "  Width: " << GetWidth() << ", Height: " << GetHeight() << "\n"
        << "  Perimeter: " << GetPerimeter() << "\n"
        << "  Area: " << GetArea() << "\n"
        << "  Outline color: #" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor << "\n"
        << "  Fill color: #" << std::hex << std::setw(6) << std::setfill('0') << m_fillColor;
    return ss.str();
}