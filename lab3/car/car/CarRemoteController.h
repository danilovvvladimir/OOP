#include "Car.h"
#include <stdio.h>
#include <tchar.h>

#include <sstream>
#include <iostream>
#include <string>
#include <functional>



#pragma once
class CarRemoteController
{
public:
	CarRemoteController(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand();
	
	//CarRemoteController& operator=(const CarRemoteController&) = delete;

private:
	bool Info(std::istream& args);
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

	std::istream& m_inputStream;
	std::ostream& m_outputStream;
	Car& m_car;

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actionMap;
};
