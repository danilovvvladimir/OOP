#pragma once
#include "../../../Point/CPoint.h"
#include "../ISolidShape.h"
#include <sstream>
#include <iomanip>

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, HexColor fillColor = DEFAULT_HEX_FILL_COLOR, HexColor outlineColor = DEFAULT_HEX_OUTPUT_COLOR);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	HexColor GetOutlineColor() const override;
	HexColor GetFillColor() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	HexColor m_fillColor;
	HexColor m_outlineColor;
};
