#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include "CCylinder.h"

CCylinder::CCylinder(double radius, double height, double density)
    : m_radius(radius), m_height(height), m_density(density)
{}

double CCylinder::GetDensity() const 
{
    return m_density;
}

double CCylinder::GetVolume() const 
{
    return M_PI * m_radius * m_radius * m_height;
}

double CCylinder::GetMass() const 
{
    return GetVolume() * m_density;
}

std::string CCylinder::ToString() const 
{
    std::ostringstream oss;
    oss << "Cylinder: "
        << "Radius = " << m_radius << ", "
        << "Height = " << m_height << ", "
        << "Density = " << m_density << ", "
        << "Volume = " << GetVolume() << ", "
        << "Mass = " << GetMass();
    return oss.str();
}
