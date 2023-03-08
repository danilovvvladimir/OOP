#include "ShapesController.h"

ShapesController::ShapesController(std::istream& input, std::ostream& output)
	: m_inputStream(input)
	, m_outputStream(output)
	, m_shapes({})
	, m_actionMap({ { "line", bind(&ShapesController::CreateLine, this, std::placeholders::_1) },
		  { "circle", bind(&ShapesController::CreateCircle, this, std::placeholders::_1) },
		  { "rectangle", bind(&ShapesController::CreateRectangle, this, std::placeholders::_1) },
		  { "triangle", bind(&ShapesController::CreateTriangle, this, std::placeholders::_1) },
		  { "help", bind(&ShapesController::Help, this, std::placeholders::_1) } })
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
	m_outputStream << "Line which starting in Point (" << leftTopPointX << ", " << leftTopPointY << ") and ending in Point ("
				   << rightBottomPointX << ", " << rightBottomPointX << ")" << std::endl
				   << " with outline color <"
				   << std::hex
				   << line.GetOutlineColor() << "> has been created." << std::endl;
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
	return true;
}

bool ShapesController::FindMaxArea(std::istream& args)
{
	return false;
}

bool ShapesController::FindMinPerimeter(std::istream& args)
{
	return false;
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
