#include "CarRemoteController.h"

CarRemoteController::CarRemoteController(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_inputStream(input)
	, m_outputStream(output)
	, m_actionMap({
		  { "Info", bind(&CarRemoteController::Info, this, std::placeholders::_1) },
		  { "EngineOn", bind(&CarRemoteController::EngineOn, this, std::placeholders::_1) },
		  { "EngineOff", bind(&CarRemoteController::EngineOff, this, std::placeholders::_1) },
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
	std::string info;
	info += "Engine: ";
	info += (m_car.IsTurnedOn() ? "ON" : "OFF");

	info += "\nDirection: ";
	switch (m_car.GetDirection())
	{
	case Direction::Stopped:
		info += "Stopped";
		break;
	case Direction::Forwards:
		info += "Forward";
		break;
	case Direction::Backwards:
		info += "Backward";
		break;
	}

	info += "\nSpeed: ";
	info += std::to_string(m_car.GetSpeed());
	info += "\nGear: ";
	info += std::to_string(static_cast<int>(m_car.GetGear()));

	m_outputStream << info << std::endl;

	return true;
}

bool CarRemoteController::EngineOn(std::istream& args)
{
	if (m_car.IsTurnedOn())
	{
		m_outputStream << "Engine is already turned ON" << std::endl;
		return true;
	}
	m_car.TurnOnEngine();

	m_outputStream << "Engine has been turned ON" << std::endl;
	return true;
}

bool CarRemoteController::EngineOff(std::istream& args)
{

	if (!m_car.IsTurnedOn())
	{
		m_outputStream << "Engine is already turned OFF" << std::endl;
		return true;
	}

	if (m_car.TurnOffEngine())
	{
		m_outputStream << "Engine has been turned OFF" << std::endl;
		return true;
	}

	m_outputStream << "You can't turn OFF the engine: the speed must be 0 and gear must be Neutral" << std::endl;
	return true;
}

bool CarRemoteController::SetGear(std::istream& args)
{
	int gear;
	std::string gearString;

	args >> gearString;
	gear = stoi(gearString);

	if (m_car.SetGear(static_cast<Gear>(gear)))
	{
		m_outputStream << "Gear has been set" << std::endl;
	}
	else
	{
		m_outputStream << "Unable to set the gear" << std::endl;
	}

	return true;
}

bool CarRemoteController::SetSpeed(std::istream& args)
{
	int speed;
	std::string speedString;

	args >> speedString;
	speed = stoi(speedString);

	if (m_car.SetSpeed(speed))
	{
		m_outputStream << "Speed has been set" << std::endl;
	}
	else
	{
		m_outputStream << "Unable to set the speed" << std::endl;
	}

	return true;
}
