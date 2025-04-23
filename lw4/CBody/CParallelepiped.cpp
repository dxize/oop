#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include <iomanip>
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
    oss << "Parallelepiped:\n\t" << std::fixed << std::setprecision(2)
        << "Width = " << m_width << "\n\t"
        << "Height = " << m_height << "\n\t"
        << "Depth = " << m_depth << "\n\t"
        << "Density = " << m_density << "\n\t"
        << "Volume = " << GetVolume() << "\n\t"
        << "Mass = " << GetMass() << "\n";
    return oss.str();
}
