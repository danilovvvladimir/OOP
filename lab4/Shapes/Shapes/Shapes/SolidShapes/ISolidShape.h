#pragma once
#include "../IShape.h"

// ask about many same #includes in Ctriangle, Crectange, CCircle

class ISolidShape : public IShape
{
public:
	virtual HexColor GetFillColor() const = 0;
};