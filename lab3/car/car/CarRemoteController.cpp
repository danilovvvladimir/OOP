#include "CarRemoteController.h"

CarRemoteController::CarRemoteController(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_inputStream(input)
	, m_outputStream(output)
	, m_actionMap({
		  { "Info", bind(&CarRemoteController::Info, this, std::placeholders::_1) },
		  { "EngineOn", bind(&CarRemoteController::EngineOn, this, std::placeholders::_1) },
		  { "EngineOf", bind(&CarRemoteController::EngineOff, this, std::placeholders::_1) },
		  { "SetSpeed", bind(&CarRemoteController::SetSpeed, this, std::placeholders::_1) },
		  { "SetGear", bind(&CarRemoteController::SetGear, this, std::placeholders::_1) },
	  })
{
}

bool CarRemoteController::HandleCommand()
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

bool CarRemoteController::Info(std::istream& args)
{
	return false;
}

bool CarRemoteController::EngineOn(std::istream& args)
{
	return false;
}

bool CarRemoteController::EngineOff(std::istream& args)
{
	return false;
}

bool CarRemoteController::SetGear(std::istream& args)
{
	return false;
}

bool CarRemoteController::SetSpeed(std::istream& args)
{
	return false;
}
