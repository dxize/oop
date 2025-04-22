#pragma once

#include <stdexcept>
#include "CBody.h"

class CSphere : public CBody
{
public:
    CSphere(double r, double d);

    double GetDensity() const override;
    double GetVolume() const override;
    double GetMass() const override;
    std::string ToString() const override;

private:
    double m_radius;
    double m_density;
};
