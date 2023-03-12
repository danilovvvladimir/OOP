#pragma once
#include "../../../Point/CPoint.h"
#include "../ISolidShape.h"
#include <iomanip>
#include <sstream>

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, HexColor fillColor, HexColor outlineColor);
	~CTriangle();

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	HexColor GetOutlineColor() const override;
	HexColor GetFillColor() const override;

	void Draw(ICanvas& canvas) override;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	HexColor m_fillColor;
	HexColor m_outlineColor;
};
