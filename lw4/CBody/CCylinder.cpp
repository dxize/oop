#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include <iomanip>
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
    oss << "Cylinder:\n\t" << std::fixed << std::setprecision(2)
        << "Radius = " << m_radius << "\n\t"
        << "Height = " << m_height << "\n\t"
        << "Density = " << m_density << "\n\t"
        << "Volume = " << GetVolume() << "\n\t"
        << "Mass = " << GetMass() << "\n";
    return oss.str(); 
}
