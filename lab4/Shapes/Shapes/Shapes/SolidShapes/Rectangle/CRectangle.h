#pragma once
#include "../../../Point/CPoint.h"
#include "../ISolidShape.h"
#include <sstream>
#include <iomanip>
class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint& leftTopPoint, const CPoint& rightBottomPoint, HexColor fillColor, HexColor outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	HexColor GetOutlineColor() const override;
	HexColor GetFillColor() const override;

	void Draw(ICanvas& canvas) override;

	CPoint GetLeftTopPoint() const;
	CPoint GetRightBottomPoint() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTopPoint;
	CPoint m_rightBottomPoint;
	HexColor m_fillColor;
	HexColor m_outlineColor;
};
