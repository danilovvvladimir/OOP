#pragma once
#include "Shapes/LineSegment/CLineSegment.h"
#include "Shapes/SolidShapes/Circle/CCircle.h"
#include "Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "Shapes/SolidShapes/Triangle/CTriangle.h"
#include <functional>
#include <map>
#include <vector>
#include <algorithm>

class ShapesController
{
public:
	ShapesController(std::istream& input, std::ostream& output);
	bool HandleCommand();
	bool PrintMaxAreaShape();
	bool PrintMinPerimeterShape();

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
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
