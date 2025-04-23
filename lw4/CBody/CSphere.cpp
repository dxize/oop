#define _USE_MATH_DEFINES
#include <cmath>
#include "CSphere.h"
#include <sstream>
#include <iomanip>

CSphere::CSphere(double r, double d) : m_radius(r), m_density(d)
{
    if (r < 0 || d < 0) {
        throw std::invalid_argument("Radius and density must be non-negative");
    }
}

double CSphere::GetDensity() const
{
    return m_density;
}

double CSphere::GetVolume() const
{
	return (4.0 / 3.0) * M_PI * m_radius * m_radius * m_radius;
}

double CSphere::GetMass() const
{
	return GetVolume() * m_density;
}

std::string CSphere::ToString() const 
{
    std::ostringstream out;
    out << "Sphere:\n\t" << std::fixed << std::setprecision(2)
        << "Radius  = " << m_radius << "\n\t"
        << "Density = " << m_density << "\n\t"
        << "Volume  = " << GetVolume() << "\n\t"
        << "Mass    = " << GetMass() << "\n";
    return out.str();
}