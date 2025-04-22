#include "CCompound.h"
#include <sstream>
#include <stdexcept>

CCompound::CCompound() = default;

bool CCompound::Contains(const std::shared_ptr<CBody>& target) const
{
    // Прямое сравнение this и target
    if (target.get() == this) 
    {
        return true;
    }

    // Рекурсивный поиск среди вложенных тел
    for (const auto& body : m_bodies) 
    {
        auto compound = std::dynamic_pointer_cast<CCompound>(body);
        if (compound && compound->Contains(target)) 
        {
            return true;
        }
    }
    return false;
}

void CCompound::AddChildBody(const std::shared_ptr<CBody>& body) 
{
    if (Contains(body)) 
    {
        throw std::logic_error("Cannot add compound body to itself or create cyclic reference.");
    }
    m_bodies.push_back(body);
}

double CCompound::GetVolume() const 
{
    double totalVolume = 0;
    for (const auto& body : m_bodies) 
    {
        totalVolume += body->GetVolume();
    }
    return totalVolume;
}

double CCompound::GetMass() const 
{
    double totalMass = 0;
    for (const auto& body : m_bodies) 
    {
        totalMass += body->GetMass();
    }
    return totalMass;
}

double CCompound::GetDensity() const 
{
    double volume = GetVolume();
    return (volume == 0) ? 0 : GetMass() / volume;
}

std::string CCompound::ToString() const 
{
    std::ostringstream oss;
    oss << "Compound body:\n";

    for (const auto& body : m_bodies) 
    {
        oss << "  - " << body->ToString() << "\n";
    }

    oss << "Total volume = " << GetVolume() << ", "
        << "Total mass = " << GetMass() << ", "
        << "Average density = " << GetDensity();

    return oss.str();
}
