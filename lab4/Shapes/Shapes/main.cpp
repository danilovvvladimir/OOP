// Папки: Point, SolidShapes, LineSegment
// using color = uint32_t ?

// CPoint - отдельный класс
// +getX getY
// -m_x m_y double
// ?????

// Интерфейс IShape, содержит 4 public метода
// -- double GetArea()
// -- double GetPerimeter()
// -- string ToString()
// -- uint32_t GetOutlineColor()
// ^
// | 1.1 1.2
// 1.1)-------Интерфейс ISolidShap
// - добавляется открытый метод -- uint32_t GetFillColor()
// ^
// | 2.1 2.2 2.3
// 2.1) класс CTriangle
// переопределение всех методов для треугольника
// Cpoint GetVertex1-3()
// 2.2) класс CRectangle
// переопределение всех методов для четырёхугольника
// Cpoint GetLeftTop, GetRightBottom
// double GetWidth, GetHeight
// 2.3) класс CCircle
// переопределение всех методов для четырёхугольника
// Cpoint GetLeftTop, GetRightBottom
// double GetRadius()
// CPoint GetCenter()

// 1.2)-------Интерфейс CLineSegment
// переопределение всех методов для линии
// CPoint GetStartPoint, GetEndPont()

// с Controller'ом так же как и в 3 лабе

// потом с SFML разобраться.

#include "Shapes/SolidShapes/Triangle/CTriangle.h"
#include <iostream>

int main()
{
	CTriangle triange(CPoint{ 0, 0 }, CPoint{ 3, 0 }, CPoint{ 2, 2 });
	std::cout << triange.ToString() << std::endl;
	CPoint p = { 1, 2 };
	return 0;
}