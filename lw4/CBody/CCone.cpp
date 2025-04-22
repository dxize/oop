#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include "CCone.h"

CCone::CCone(double radius, double height, double density)
    : m_radius(radius), m_height(height), m_density(density)
{}

double CCone::GetDensity() const 
{
    return m_density;
}

double CCone::GetVolume() const 
{
    return (1.0 / 3.0) * M_PI * m_radius * m_radius * m_height;
}

double CCone::GetMass() const 
{
    return GetVolume() * m_density;
}

std::string CCone::ToString() const 
{
    std::ostringstream oss;
    oss << "Cone: "
        << "Radius = " << m_radius << ", "
        << "Height = " << m_height << ", "
        << "Density = " << m_density << ", "
        << "Volume = " << GetVolume() << ", "
        << "Mass = " << GetMass();
    return oss.str();
}
