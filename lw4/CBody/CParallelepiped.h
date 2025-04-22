#pragma once
#include "CBody.h"

class CParallelepiped : public CBody 
{
public:

    CParallelepiped(double width, double height, double depth, double density);

    double GetDensity() const override;
    double GetVolume() const override;
    double GetMass() const override;
    std::string ToString() const override;
private:
    double m_width;
    double m_height;
    double m_depth;
    double m_density;
};
