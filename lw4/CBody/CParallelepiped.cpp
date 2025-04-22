#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include "CParallelepiped.h"

CParallelepiped::CParallelepiped(double width, double height, double depth, double density)
    : m_width(width), m_height(height), m_depth(depth), m_density(density)
{}

double CParallelepiped::GetDensity() const 
{
    return m_density;
}

double CParallelepiped::GetVolume() const 
{
    return m_width * m_height * m_depth;
}

double CParallelepiped::GetMass() const 
{
    return m_density * GetVolume();
}

std::string CParallelepiped::ToString() const 
{
    std::ostringstream oss;
    oss << "Parallelepiped: "
        << "Width = " << m_width << ", "
        << "Height = " << m_height << ", "
        << "Depth = " << m_depth << ", "
        << "Density = " << m_density << ", "
        << "Volume = " << GetVolume() << ", "
        << "Mass = " << GetMass();
    return oss.str();
}
