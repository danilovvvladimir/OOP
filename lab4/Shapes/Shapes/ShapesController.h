#pragma once
#include "Shapes/LineSegment/CLineSegment.h"
#include "Shapes/SolidShapes/Circle/CCircle.h"
#include "Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "Shapes/SolidShapes/Triangle/CTriangle.h"
#include <algorithm>
#include <functional>
#include <map>
#include <vector>
#include "CCanvas.h"

struct ArgsLine
{
	CPoint startPoint;
	CPoint endPoint;
	HexColor outlineColor;
};
struct ArgsTriangle
{
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;
	HexColor fillColor;
	HexColor outlineColor;
};
struct ArgsRectangle
{
	CPoint leftTopPoint;
	CPoint rightBottomPoint;
	HexColor fillColor;
	HexColor outlineColor;
};
struct ArgsCircle
{
	CPoint centerPoint;
	double radius;
	HexColor fillColor;
	HexColor outlineColor;
};

class ShapesController
{
public:
	ShapesController(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintMaxAreaShape();
	void PrintMinPerimeterShape();
	void DrawShaped(unsigned width, unsigned height, const std::string& windowTitle) const;

private:
	enum class Shape
	{
		CIRCLE,
		TRIANGLE,
		RECTANGLE,
		LINE,
	};

	bool CreateLine(std::istream& args);
	bool CreateCircle(std::istream& args);
	bool CreateRectangle(std::istream& args);
	bool CreateTriangle(std::istream& args);
	bool PrintAllShapes(std::istream& args);
	bool Help(std::istream& args);

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	ActionMap m_actionMap;
	std::istream& m_inputStream;
	std::ostream& m_outputStream;

	std::shared_ptr<CCircle> c;
	using IShapePointer = std::shared_ptr<IShape>;
	std::vector<IShapePointer> m_shapes;
};
