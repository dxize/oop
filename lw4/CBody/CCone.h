#pragma once
#include "CBody.h"

class CCone : public CBody 
{
public:
    CCone(double radius, double height, double density);
 
    double GetDensity() const override;
    double GetVolume() const override;
    double GetMass() const override;
    std::string ToString() const override;
private:
    double m_radius;
    double m_height;
    double m_density;
};
