#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include <iomanip>
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
    oss << "Cone:\n\t" << std::fixed << std::setprecision(2)
        << "Radius = " << m_radius << "\n\t"
        << "Height = " << m_height << "\n\t"
        << "Density = " << m_density << "\n\t"
        << "Volume = " << GetVolume() << "\n\t"
        << "Mass = " << GetMass() << "\n";
    return oss.str();
}
