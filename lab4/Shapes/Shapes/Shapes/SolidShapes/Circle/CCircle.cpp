#include "CCircle.h"

CCircle::CCircle(const CPoint& centerPoint, double radius, HexColor fillColor, HexColor outlineColor)
	: m_centerPoint(centerPoint)
	, m_radius(radius)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::ostringstream outputStream;
	outputStream << std::fixed << std::setprecision(2)
				 << "CIRCLE" << std::endl
				 << "Center: (" << m_centerPoint.GetPointX() << ", " << m_centerPoint.GetPointY() << ")" << std::endl
				 << "Radius: " << m_radius << std::endl
				 << "Outline Color: #" << std::hex << GetOutlineColor() << std::endl
				 << "Fill Color: #" << std::hex << GetFillColor() << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimiter: " << GetPerimeter() << std::endl;
	return outputStream.str();
}

HexColor CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

HexColor CCircle::GetFillColor() const
{
	return m_fillColor;
}

void CCircle::Draw(ICanvas& canvas)
{
	canvas.FillCircle(m_centerPoint, m_radius, m_fillColor);
	canvas.DrawCircle(m_centerPoint, m_radius, m_outlineColor);
}

double CCircle::GetRadius() const
{
	return m_radius;
}

CPoint CCircle::GetCenterPoint() const
{
	return m_centerPoint;
}
