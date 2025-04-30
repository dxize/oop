#include "CCompound.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <memory>


CCompound::CCompound() = default;

bool CCompound::Contains(const std::shared_ptr<CBody>& target) const
{
    // 1) Прямое добавление себя запрещено
    if (target.get() == this) {
        return true;
    }
    // 2) Рекурсивный поиск среди уже добавленных составных тел
    for (const auto& child : m_bodies) {
        if (auto cmp = std::dynamic_pointer_cast<CCompound>(child)) {
            if (cmp->Contains(target)) {
                return true;
            }
        }
    }
    return false;
}

void CCompound::AddChildBody(const std::shared_ptr<CBody>& body)
{
    // Не добавляем самого себя
    if (body.get() == this) {
        throw std::logic_error("Cannot add itself to compound");
    }
    // Если добавляемое тело составное и оно содержит текущий — запрет циклической ссылки
    if (auto cmp = std::dynamic_pointer_cast<CCompound>(body)) {
        if (cmp->Contains(shared_from_this())) {
            throw std::logic_error("Cannot add compound body to itself or create cyclic reference.");
        }
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
    return ToStringImpl(0);
}

std::string CCompound::ToStringImpl(int indent) const
{
    std::ostringstream oss;
    std::string pad(indent, ' ');
    oss << pad << "Compound:\n";

    for (auto& body : m_bodies) {
        // если это вложенный компаунд — увеличиваем отступ
        if (auto cb = std::dynamic_pointer_cast<CCompound>(body)) {
            oss << cb->ToStringImpl(indent + 2);
        }
        else {
            // простое тело — выводим одной строкой, с отступом
            oss << pad << "  - " << body->ToString() << "\n";
        }
    }

    oss << pad << std::fixed << std::setprecision(2)
        << "Total volume = " << GetVolume() << "\n"
        << pad << "Total mass = " << GetMass() << "\n"
        << pad << "Avg density = " << GetDensity() << "\n";
    return oss.str();
}

