#pragma once
#include "../../../Point/CPoint.h"
#include "../ISolidShape.h"
#include <iomanip>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>


class CCircle : public ISolidShape
{
public:
	CCircle(const CPoint& centerPoint, double radius, HexColor fillColor, HexColor outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	HexColor GetOutlineColor() const override;
	HexColor GetFillColor() const override;

	double GetRadius() const;
	CPoint GetCenterPoint() const;

private:
	CPoint m_centerPoint;
	double m_radius;
	HexColor m_fillColor;
	HexColor m_outlineColor;
};
