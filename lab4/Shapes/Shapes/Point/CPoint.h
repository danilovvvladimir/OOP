#pragma once
#include <cmath>
class CPoint
{
public:
	CPoint(double x, double y);
	double GetPointX() const;
	double GetPointY() const;
	// static
	static double GetDistance(const CPoint& point1, const CPoint& point2);
	bool operator==(const CPoint& otherPoint) const;

private:
	double m_x;
	double m_y;
};
