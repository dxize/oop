#include "CBodyManager.h"
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>


void CBodyManager::AddBody(const std::shared_ptr<CBody>& body) 
{
    if (!body) 
    {
        throw std::invalid_argument("Cannot add null body");
    }
    m_bodies.push_back(body);
}

// Вывести в консоль информацию обо всех телах
void CBodyManager::PrintAll() const 
{
    for (const auto& b : m_bodies) 
    {
        std::cout << b->ToString() << "\n\n";
    }
}

// Найти тело с максимальной массой
std::shared_ptr<CBody> CBodyManager::FindMaxMass() const 
{
    if (m_bodies.empty()) 
    {
        return nullptr;
    }
    auto it = std::max_element(
        m_bodies.begin(), m_bodies.end(),
        [](auto& a, auto& b) { return a->GetMass() < b->GetMass(); }
    );
    return *it;
}

// Найти тело с минимальным "весом в воде"
std::shared_ptr<CBody> CBodyManager::FindMinWeightInWater() const 
{
    if (m_bodies.empty()) 
    {
        return nullptr;
    }
    constexpr double waterDensity = 1000.0;
    auto it = std::min_element(
        m_bodies.begin(), m_bodies.end(),
        [waterDensity](auto& a, auto& b) 
        {
            double wa = a->GetMass() - waterDensity * a->GetVolume();
            double wb = b->GetMass() - waterDensity * b->GetVolume();
            return wa < wb;
        }
    );
    return *it;
}