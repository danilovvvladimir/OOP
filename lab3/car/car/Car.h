#pragma once
#include <map>
#include <iostream>

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

const int MIN_SPEED = 0;
const int MAX_SPEED = 150;

enum class Direction
{
	Backwards = -1,
	Stopped,
	Forwards,
};

enum class Gear
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
using GearsSpeedInterval = std::map<Gear, SpeedInterval>;

const GearsSpeedInterval gearsSpeedIntervals = {
	{ Gear::Reversed, { MIN_SPEED, 20 } },
	{ Gear::Neutral, { MIN_SPEED , MAX_SPEED} },
	{ Gear::First, {0, 30} },
	{ Gear::Second, {20, 50} },
	{ Gear::Third, {30, 60} },
	{ Gear::Thourth, {40, 90} },
	{ Gear::Fifth, { 50, MAX_SPEED } }
};


class Car
{
public:
	Car();

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	Gear GetGear() const;
	int GetSpeed() const; 

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetSpeed(int speed);

	void PrintInfo();

private:
	bool m_isEngineOn;
	int m_speed;
	Gear m_gear;
	Direction m_direction;
};
