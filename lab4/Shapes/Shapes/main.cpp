// �����: Point, SolidShapes, LineSegment
// using color = uint32_t ?

// CPoint - ��������� �����
// +getX getY
// -m_x m_y double
// ?????

// ��������� IShape, �������� 4 public ������
// -- double GetArea()
// -- double GetPerimeter()
// -- string ToString()
// -- uint32_t GetOutlineColor()
// ^
// | 1.1 1.2
// 1.1)-------��������� ISolidShap
// - ����������� �������� ����� -- uint32_t GetFillColor()
// ^
// | 2.1 2.2 2.3
// 2.1) ����� CTriangle
// ��������������� ���� ������� ��� ������������
// Cpoint GetVertex1-3()
// 2.2) ����� CRectangle
// ��������������� ���� ������� ��� ���������������
// Cpoint GetLeftTop, GetRightBottom
// double GetWidth, GetHeight
// 2.3) ����� CCircle
// ��������������� ���� ������� ��� ���������������
// Cpoint GetLeftTop, GetRightBottom
// double GetRadius()
// CPoint GetCenter()

// 1.2)-------��������� CLineSegment
// ��������������� ���� ������� ��� �����
// CPoint GetStartPoint, GetEndPont()

// � Controller'�� ��� �� ��� � � 3 ����

// ����� � SFML �����������.

#include "Shapes/SolidShapes/Triangle/CTriangle.h"
#include <iostream>

int main()
{
	CTriangle triange(CPoint{ 0, 0 }, CPoint{ 3, 0 }, CPoint{ 2, 2 });
	std::cout << triange.ToString() << std::endl;
	CPoint p = { 1, 2 };
	return 0;
}