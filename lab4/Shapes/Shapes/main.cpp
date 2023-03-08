// с Controller'ом так же как и в 3 лабе

// потом с SFML разобраться.

#include "Shapes/SolidShapes/Triangle/CTriangle.h"
#include "Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "Shapes/LineSegment/CLineSegment.h"
#include <iostream>

int main()
{
	CPoint triangleVertex1 = { 0, 0 };
	CPoint triangleVertex2 = { -3, -2 };
	CPoint triangleVertex3 = { 2, 2 };
	HexColor triangleFillColor = 0xff00ff;
	HexColor triangleOutlineColor = 0x00ff00;

	CTriangle triangle(triangleVertex1, triangleVertex2, triangleVertex3, triangleFillColor, triangleOutlineColor);
	
	std::cout << triangle.ToString() << std::endl;
	return 0;
}