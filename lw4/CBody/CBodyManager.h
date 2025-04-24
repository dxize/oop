#pragma once

#include <vector>
#include <memory>
#include "CBody.h"

class CBodyManager 
{
public:
    void AddBody(const std::shared_ptr<CBody>& body);
    void PrintAll() const;
    std::shared_ptr<CBody> FindMaxMass() const;
    std::shared_ptr<CBody> FindMinWeightInWater() const;
private:
    std::vector<std::shared_ptr<CBody>> m_bodies;
};
