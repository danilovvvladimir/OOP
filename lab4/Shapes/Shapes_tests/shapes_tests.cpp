#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Shapes/Point/CPoint.h"
#include "../Shapes/Shapes/LineSegment/CLineSegment.h"
#include "../Shapes/Shapes/SolidShapes/Circle/CCircle.h"
#include "../Shapes/Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "../Shapes/Shapes/SolidShapes/Triangle/CTriangle.h"

SCENARIO("Testing CPoint")
{
	WHEN("Init CPoint")
	{
		CPoint point(12.3, 45.67);
		REQUIRE(point.GetPointX() == 12.3);
		REQUIRE(point.GetPointY() == 45.67);
	}
	WHEN("GetDistance between two points")
	{
		CPoint point1(2, -5);
		CPoint point2(-4, 3);
		double correctDistance = sqrt(pow((point2.GetPointX() - point1.GetPointX()), 2) + pow((point2.GetPointY() - point1.GetPointY()), 2));
		REQUIRE(CPoint::GetDistance(point1, point2) == correctDistance);
	}
}

SCENARIO("Testing Triangle")
{
	CPoint triangleVertex1 = { 0, 0 };
	CPoint triangleVertex2 = { 3, 0 };
	CPoint triangleVertex3 = { 2, 2 };
	HexColor triangleFillColor = 0xff00ff;
	HexColor triangleOutlineColor = 0x00ff00;
	
	CTriangle triangle(triangleVertex1, triangleVertex2, triangleVertex3, triangleFillColor, triangleOutlineColor);
	WHEN("Testing GetVertixes")
	{
		REQUIRE(triangle.GetVertex1() == triangleVertex1);
		REQUIRE(triangle.GetVertex2() == triangleVertex2);
		REQUIRE(triangle.GetVertex3() == triangleVertex3);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(triangle.GetFillColor() == triangleFillColor);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(triangle.GetOutlineColor() == triangleOutlineColor);
	}

	double distanceVertex12 = CPoint::GetDistance(triangle.GetVertex1(), triangle.GetVertex2());
	double distanceVertex13 = CPoint::GetDistance(triangle.GetVertex1(), triangle.GetVertex3());
	double distanceVertex23 = CPoint::GetDistance(triangle.GetVertex2(), triangle.GetVertex3());

	WHEN("Testing GetPerimeter")
	{
		double correctTrianglePerimeter = distanceVertex12 + distanceVertex13 + distanceVertex23;
		REQUIRE(triangle.GetPerimeter() == correctTrianglePerimeter);
	}
	WHEN("Testing GetArea")
	{
		double halfPerimeter = triangle.GetPerimeter() / 2;
		double correctTriangleArea = sqrt(halfPerimeter * (halfPerimeter - distanceVertex12) * (halfPerimeter - distanceVertex12) * (halfPerimeter - distanceVertex12));
		REQUIRE(triangle.GetArea() == correctTriangleArea);
	}
}