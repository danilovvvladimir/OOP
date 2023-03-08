#include "ShapesController.h"

ShapesController::ShapesController(std::istream& input, std::ostream& output)
	: m_inputStream(input)
	, m_outputStream(output)
	, m_shapes({})
	, m_actionMap({ { "line", bind(&ShapesController::CreateLine, this, std::placeholders::_1) },
		  { "circle", bind(&ShapesController::CreateCircle, this, std::placeholders::_1) },
		  { "rectangle", bind(&ShapesController::CreateRectangle, this, std::placeholders::_1) },
		  { "triangle", bind(&ShapesController::CreateTriangle, this, std::placeholders::_1) },
		  { "help", bind(&ShapesController::Help, this, std::placeholders::_1) },
		  { "printAllShapes", bind(&ShapesController::PrintAllShapes, this, std::placeholders::_1) } })
{
}

bool ShapesController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_inputStream, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);

	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool ShapesController::CreateLine(std::istream& args)
{
	if (args.eof())
	{
		m_outputStream << "Correct usage:" << std::endl
					   << "\t line <startPoint X> <startPoint Y> <endPoint X> <endPoint Y> <hex fillColor?> <hex outlineColor?>" << std::endl;
		return false;
	}

	double leftTopPointX;
	double leftTopPointY;
	double rightBottomPointX;
	double rightBottomPointY;
	HexColor outlineColor;

	args >> leftTopPointX >> leftTopPointY >> rightBottomPointX >> rightBottomPointY >> std::hex >> outlineColor;
	if (args.fail())
	{
		m_outputStream << "Not Enough arguments!!!" << std::endl
					   << "Correct usage:" << std::endl
					   << "\t line <startPoint X> <startPoint Y> <endPoint X> <endPoint Y> <hex outlineColor?>" << std::endl;
		return false;
	}

	CLineSegment line(CPoint{ leftTopPointX, leftTopPointY }, CPoint{ rightBottomPointX, rightBottomPointY }, outlineColor);
	m_shapes.push_back(std::make_shared<CLineSegment>(line));
	m_outputStream << "Line has been created." << std::endl;
	return true;
}

bool ShapesController::CreateCircle(std::istream& args)
{
	if (args.eof())
	{
		m_outputStream << "Correct usage:" << std::endl
					   << "\t circle <centerPoint X> <centerPoint Y> <radius> <hex fillColor?> <hex outlineColor?>" << std::endl;
		return false;
	}

	double centerPointX;
	double centerPointY;
	double radius;
	HexColor fillColor;
	HexColor outlineColor;

	args >> centerPointX >> centerPointY >> radius >> std::hex >> fillColor >> outlineColor;
	if (args.fail())
	{
		m_outputStream << "Not Enough arguments!!!" << std::endl
					   << "Correct usage:" << std::endl
					   << "\t circle <centerPoint X> <centerPoint Y> <radius> <hex fillColor?> <hex outlineColor?>" << std::endl;
		return false;
	}

	CCircle circle(CPoint{ centerPointX, centerPointY }, radius, fillColor, outlineColor);
	m_shapes.push_back(std::make_shared<CCircle>(circle));
	m_outputStream << "Circle has been created." << std::endl;
	return true;
}

bool ShapesController::CreateRectangle(std::istream& args)
{
	if (args.eof())
	{
		m_outputStream << "Correct usage:" << std::endl
					   << "\t rectangle <leftTopPoint X> <leftTopPointY> <rightBottomPoint X> <rightBottomPoint Y> <hex fillColor?> <hex outlineColor?>" << std::endl;
		return false;
	}

	double leftTopPointX;
	double leftTopPointY;
	double rightBottomPointX;
	double rightBottomPointY;
	HexColor fillColor;
	HexColor outlineColor;

	args >> leftTopPointX >> leftTopPointY >> rightBottomPointX >> rightBottomPointY >> std::hex >> fillColor >> outlineColor;
	if (args.fail())
	{
		m_outputStream << "Not Enough arguments!!!" << std::endl
					   << "Correct usage:" << std::endl
					   << "\t rectangle <leftTopPoint X> <leftTopPointY> <rightBottomPoint X> <rightBottomPoint Y> <hex fillColor?> <hex outlineColor?>" << std::endl;
		return false;
	}

	CRectangle rectangle(CPoint{ leftTopPointX, leftTopPointY }, CPoint{ rightBottomPointX, rightBottomPointY }, fillColor, outlineColor);

	m_shapes.push_back(std::make_shared<CRectangle>(rectangle));
	m_outputStream << "Rectangle has been created." << std::endl;
	return true;
}

bool ShapesController::CreateTriangle(std::istream& args)
{
	if (args.eof())
	{
		m_outputStream << "Correct usage:" << std::endl
					   << "\t triangle <vertex1 X> <vertex1 Y> <vertex2 X> <vertex2 Y> <vertex3 X> <vertex3 Y> <hex fillColor?> <hex outlineColor?>" << std::endl;
		return false;
	}

	double vertex1X;
	double vertex1Y;
	double vertex2X;
	double vertex2Y;
	double vertex3X;
	double vertex3Y;
	HexColor fillColor;
	HexColor outlineColor;

	args >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y >> std::hex >> fillColor >> outlineColor;
	if (args.fail())
	{
		m_outputStream << "Not Enough arguments!!!" << std::endl
					   << "Correct usage:" << std::endl
					   << "\t triangle <vertex1 X> <vertex1 Y> <vertex2 X> <vertex2 Y> <vertex3 X> <vertex3 Y> <hex fillColor?> <hex outlineColor?>" << std::endl;
		return false;
	}

	CTriangle triangle(CPoint{ vertex1X, vertex1Y }, CPoint{ vertex2X, vertex2Y }, CPoint{ vertex3X, vertex3Y }, fillColor, outlineColor);

	m_shapes.push_back(std::make_shared<CTriangle>(triangle));
	m_outputStream << "Rectangle has been created." << std::endl;

	return true;
}

bool ShapesController::PrintMaxAreaShape()
{
	if (m_shapes.size() == 0)
	{
		m_outputStream << "There are no shapes yet" << std::endl;
		return false;
	}

	auto maxAreaShapeIt = std::max_element(m_shapes.begin(),
		m_shapes.end(),
		[](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2) { return shape1->GetArea() < shape2->GetArea(); });
	m_outputStream << (*maxAreaShapeIt)->ToString() << std::endl;
	return true;
}

bool ShapesController::PrintMinPerimeterShape()
{
	if (m_shapes.size() == 0)
	{
		m_outputStream << "There are no shapes yet" << std::endl;
		return false;
	}

	auto minPerimeterShape = std::max_element(m_shapes.begin(),
		m_shapes.end(),
		[](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2) { return shape1->GetPerimeter() > shape2->GetPerimeter(); });
	m_outputStream << (*minPerimeterShape)->ToString() << std::endl;
	return true;
}

bool ShapesController::PrintAllShapes(std::istream& args)
{
	for (auto &shape : m_shapes)
	{
		m_outputStream << shape->ToString() << std::endl;
	}
	return true;
}

bool ShapesController::Help(std::istream& args)
{
	std::ostringstream helpStream;
	m_outputStream << std::fixed << std::setprecision(2)
				   << "AVAILABLE COMMANDS:" << std::endl
				   << "-> info: show available commands" << std::endl
				   << "-> rectangle <leftTopPoint X> <leftTopPointY> <rightBottomPoint X>" << std::endl
				   << "<rightBottomPoint Y> <hex fillColor?> <hex outlineColor?>" << std::endl
				   << "   - creating rectangle using two points's coordinates " << std::endl
				   << "     and optional color set" << std::endl
				   << std::endl
				   << "-> circle <centerPoint X> <centerPoint Y> " << std::endl
				   << "<radius> <hex fillColor?> <hex outlineColor?>" << std::endl
				   << "   - creating circle using centerPoint's coordinates & radius, " << std::endl
				   << "     and optional color set" << std::endl
				   << std::endl
				   << "-> triangle <vertex1 X> <vertex1 Y> <vertex2 X> " << std::endl
				   << "<vertex2 Y> <vertex3 X> <vertex3 Y> <hex fillColor?> <hex outlineColor?>" << std::endl
				   << "   - creating triangle with three vertexes's coordinates " << std::endl
				   << "     and optional color set" << std::endl
				   << std::endl
				   << "-> line <startPoint X> <startPoint Y> <endPoint X> " << std::endl
				   << "<endPoint Y> <hex outlineColor?>" << std::endl
				   << "   - creating line with two point's coordinates " << std::endl
				   << "     and optional color set" << std::endl
				   << std::endl
				   << "-> maxarea" << std::endl
				   << "   - finding max area of all available shapes " << std::endl
				   << "-> minperimeter" << std::endl
				   << "   - finding min perimeter of all available shapes " << std::endl;
	return true;
}
