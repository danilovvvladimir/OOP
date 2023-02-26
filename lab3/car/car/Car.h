#pragma once
#include <map>

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

const int MIN_SPEED = 0;
const int MAX_SPEED = 150;

enum class Direction
{
	Backwards,
	Forwards,
	Stopped,
};

enum class Gears
{
	Reversed = MIN_GEAR,
	Neutral,
	First,
	Second,
	Third,
	Thourth,
	Fifth,
};

using SpeedInterval = std::pair<int, int>;
using GearsSpeedInterval = std::map<Gears, SpeedInterval>;

const GearsSpeedInterval gearsSpeedInterval = {
	{ Gears::Reversed, { MIN_SPEED, 20 } },
	{ Gears::Neutral, { MIN_SPEED , MAX_SPEED} },
	{ Gears::First, {0, 30} },
	{ Gears::Second, {20, 50} },
	{ Gears::Third, {30, 60} },
	{ Gears::Thourth, {40, 90} },
	{ Gears::Fifth, { 50, MAX_SPEED } }
};


class Car
{
public:
	

	Car();

	bool IsTurnedOn() const;
	int GetDirection() const;
	int GetSpeed() const; 
	int GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool m_isEngineOn;
	int m_speed;
	int m_gear;
};
