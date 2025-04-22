#pragma once
#include "CBody.h"
#include <vector>
#include <memory>

class CCompound : public CBody 
{
public:
    CCompound();

    void AddChildBody(const std::shared_ptr<CBody>& body);

    double GetDensity() const override;
    double GetVolume() const override;
    double GetMass() const override;
    std::string ToString() const override;
private:
    std::vector<std::shared_ptr<CBody>> m_bodies;
    bool Contains(const std::shared_ptr<CBody>& target) const;
};
