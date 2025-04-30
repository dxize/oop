#pragma once
#include "IShape.h"
#include <cstdint>
#include <string>

class ISolidShape: public IShape
{
public:
	virtual ~ISolidShape() = default;
	virtual uint32_t GetFillColor() const = 0;
};
