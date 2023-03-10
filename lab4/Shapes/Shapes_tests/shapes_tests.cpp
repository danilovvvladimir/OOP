#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Shapes/CCanvas.h"
#include "../Shapes/Point/CPoint.h"
#include "../Shapes/Shapes/LineSegment/CLineSegment.h"
#include "../Shapes/Shapes/SolidShapes/Circle/CCircle.h"
#include "../Shapes/Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "../Shapes/Shapes/SolidShapes/Triangle/CTriangle.h"
#include "../Shapes/ShapesController.h"

SCENARIO("Testing CPoint")
{
	WHEN("Init CPoint with coordinates")
	{
		THEN("CPoint is correctly inited")
		{
			CPoint point(12.3, 45.67);
			REQUIRE(point.GetPointX() == 12.3);
			REQUIRE(point.GetPointY() == 45.67);
		}
	}
	WHEN("GetDistance between two points")
	{
		THEN("Distance between two points equals correctDistance")
		{
			CPoint point1(2, -5);
			CPoint point2(-4, 3);
			double correctDistance = sqrt(pow((point2.GetPointX() - point1.GetPointX()), 2) + pow((point2.GetPointY() - point1.GetPointY()), 2));
			REQUIRE(CPoint::GetDistance(point1, point2) == correctDistance);
		}
	}
	WHEN("Comparison identical CPoints")
	{
		THEN("Point are equal")
		{
			CPoint point1(12.3, 45.67);
			CPoint point2(12.3, 45.67);
			REQUIRE(point1 == point2);
		}
	}
	WHEN("Comparison non-identical CPoints")
	{
		THEN("Point are not equal")
		{
			CPoint point1(12.3, 45.67);
			CPoint point2(12.3, 45.68);
			REQUIRE(!(point1 == point2));
		}
	}
}

SCENARIO("Testing CTriangle")
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

SCENARIO("Testing CRectangleee")
{
	CPoint rectangleLeftTopPoint = { 0, 10 };
	CPoint rectangleRightBottomPoint = { 10, 0 };

	HexColor rectangleFillColor = 0xff00ff;
	HexColor rectangleOutlineColor = 0x00ff00;

	CRectangle rectangle(rectangleLeftTopPoint, rectangleRightBottomPoint, rectangleFillColor, rectangleOutlineColor);

	WHEN("Testing Get Point")
	{
		REQUIRE(rectangle.GetLeftTopPoint() == rectangleLeftTopPoint);
		REQUIRE(rectangle.GetRightBottomPoint() == rectangleRightBottomPoint);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(rectangle.GetFillColor() == rectangleFillColor);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(rectangle.GetOutlineColor() == rectangleOutlineColor);
	}

	double rectangleCorrectWidth = rectangleRightBottomPoint.GetPointX() - rectangleLeftTopPoint.GetPointX();
	double rectangleCorrectHeight = rectangleLeftTopPoint.GetPointY() - rectangleRightBottomPoint.GetPointY();
	WHEN("Testing GetWidth")
	{
		REQUIRE(rectangle.GetWidth() == rectangleCorrectWidth);
	}
	WHEN("Testing GetHeight")
	{

		REQUIRE(rectangle.GetHeight() == rectangleCorrectHeight);
	}

	WHEN("Testing GetPerimeter")
	{
		double rectangleCorrectPerimeter = (rectangleCorrectWidth + rectangleCorrectHeight) * 2;
		REQUIRE(rectangle.GetPerimeter() == rectangleCorrectPerimeter);
	}
	WHEN("Testing GetArea")
	{
		double rectangleCorrectArea = rectangleCorrectWidth * rectangleCorrectHeight;
		REQUIRE(rectangle.GetArea() == rectangleCorrectArea);
	}
}

SCENARIO("Testing CCircle")
{
	CPoint circleCenterPoint = { 5, 5 };
	double circleRadius = 5;

	HexColor circleFillColor = 0xff00ff;
	HexColor circleOutlineColor = 0x00ff00;

	CCircle circle(circleCenterPoint, circleRadius, circleFillColor, circleOutlineColor);

	WHEN("Testing GetCenterPoint")
	{
		REQUIRE(circle.GetCenterPoint() == circleCenterPoint);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(circle.GetFillColor() == circleFillColor);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(circle.GetOutlineColor() == circleOutlineColor);
	}
	WHEN("Testing GetPerimeter")
	{
		double circleCorrectPerimeter = 2 * circleRadius * M_PI;
		REQUIRE(circle.GetPerimeter() == circleCorrectPerimeter);
	}
	WHEN("Testing GetArea")
	{
		double circleCorrectArea = 2 * circleRadius * circleRadius * M_PI;
		REQUIRE(circle.GetArea() == circleCorrectArea);
	}
}

SCENARIO("Testing CLineSegment")
{
	CPoint lineStartPoint = { 0, 0 };
	CPoint lineEndPoint = { 5, 0 };

	HexColor lineOutlineColor = 0x00ff00;

	CLineSegment line(lineStartPoint, lineEndPoint, lineOutlineColor);

	WHEN("Testing GetStartPoint")
	{
		REQUIRE(line.GetStartPoint() == lineStartPoint);
	}
	WHEN("Testing GetEndPoint")
	{
		REQUIRE(line.GetEndPoint() == lineEndPoint);
	}
	WHEN("Testing GetFillColor")
	{
		REQUIRE(line.GetOutlineColor() == lineOutlineColor);
	}
	WHEN("Testing GetPerimeter")
	{
		double lineCorrectPerimeter = CPoint::GetDistance(lineEndPoint, lineStartPoint);
		REQUIRE(line.GetPerimeter() == lineCorrectPerimeter);
	}
	WHEN("Testing GetArea")
	{
		double lineCorrectArea = 0;
		REQUIRE(line.GetArea() == lineCorrectArea);
	}
}

SCENARIO("Testing ShapeController")
{
	WHEN("Creating Line using ShapeController")
	{
		THEN("Line has been successfully created")
		{
			std::istringstream inputStream("line 0 0 5 5 ff00ffff \nprintAllShapes");
			std::ostringstream outputStream;
			ShapesController shapesController(inputStream, outputStream);

			shapesController.HandleCommand();
			shapesController.HandleCommand();

			std::ostringstream correctOutputStream;
			correctOutputStream << "Line has been created." << std::endl
								<< "LINE" << std::endl
								<< "Start Point: (0.00, 0.00)" << std::endl
								<< "End Point: (5.00, 5.00)" << std::endl
								<< "Outline Color: #ff00ffff" << std::endl
								<< "Area: 0.00" << std::endl
								<< "Perimiter: 7.07" << std::endl
								<< std::endl;
			REQUIRE(outputStream.str() == correctOutputStream.str());
		}
	}
	WHEN("Creating Triangle using ShapeController")
	{
		THEN("Triangle has been successfully created")
		{
			std::istringstream inputStream("triangle 0 0 5 5 2 2 ff00ffff fefefeff\nprintAllShapes");
			std::ostringstream outputStream;
			ShapesController shapesController(inputStream, outputStream);

			shapesController.HandleCommand();
			shapesController.HandleCommand();

			std::ostringstream correctOutputStream;
			correctOutputStream << "Triangle has been created." << std::endl
								<< "TRIANGLE" << std::endl
								<< "Vertex #1: (0.00, 0.00)" << std::endl
								<< "Vertex #2: (5.00, 5.00)" << std::endl
								<< "Vertex #3: (2.00, 2.00)" << std::endl
								<< "Outline Color: #fefefeff" << std::endl
								<< "Fill Color: #ff00ffff" << std::endl
								<< "Area: 0.00" << std::endl
								<< "Perimiter: 14.14" << std::endl
								<< std::endl;
			REQUIRE(outputStream.str() == correctOutputStream.str());
		}
	}
	WHEN("Creating Rectangle using ShapeController")
	{
		THEN("Rectangle has been successfully created")
		{
			std::istringstream inputStream("rectangle 10 10 15 0 ff00ffff fefefeff\nprintAllShapes");
			std::ostringstream outputStream;
			ShapesController shapesController(inputStream, outputStream);

			shapesController.HandleCommand();
			shapesController.HandleCommand();

			std::ostringstream correctOutputStream;
			correctOutputStream << "Rectangle has been created." << std::endl
								<< "RECTANGLE" << std::endl
								<< "Left Top Point: (10.00, 10.00)" << std::endl
								<< "Right Bottom Point: (15.00, 0.00)" << std::endl
								<< "Width: 5.00" << std::endl
								<< "Height: 10.00" << std::endl
								<< "Outline Color: #fefefeff" << std::endl
								<< "Fill Color: #ff00ffff" << std::endl
								<< "Area: 50.00" << std::endl
								<< "Perimiter: 30.00" << std::endl
								<< std::endl;
			REQUIRE(outputStream.str() == correctOutputStream.str());
		}
	}
	WHEN("Creating Circle using ShapeController")
	{
		THEN("Circle has been successfully created")
		{
			std::istringstream inputStream("circle 0 0 5 ff00ffff fefefeff\nprintAllShapes");
			std::ostringstream outputStream;
			ShapesController shapesController(inputStream, outputStream);

			shapesController.HandleCommand();
			shapesController.HandleCommand();

			std::ostringstream correctOutputStream;
			correctOutputStream << "Circle has been created." << std::endl
								<< "CIRCLE" << std::endl
								<< "Center: (0.00, 0.00)" << std::endl
								<< "Radius: 5.00" << std::endl
								<< "Outline Color: #fefefeff" << std::endl
								<< "Fill Color: #ff00ffff" << std::endl
								<< "Area: 157.08" << std::endl
								<< "Perimiter: 31.42" << std::endl
								<< std::endl;
			REQUIRE(outputStream.str() == correctOutputStream.str());
		}
	}
}