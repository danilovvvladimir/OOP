#pragma once
#include <map>


const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

const int MIN_SPEED = 0;
const int MAX_SPEED = 150;

const int REVERSED_GEAR_MIN_SPEED = MIN_SPEED;
const int REVERSED_GEAR_MAX_SPEED = 20;

const int FIRST_GEAR_MIN_SPEED = MIN_SPEED;
const int FIRST_GEAR_MAX_SPEED = 30;

const int SECOND_GEAR_MIN_SPEED = 20;
const int SECOND_GEAR_MAX_SPEED = 50;

const int THIRD_GEAR_MIN_SPEED = 30;
const int THIRD_GEAR_MAX_SPEED = 60;

const int FOURTH_GEAR_MIN_SPEED = 40;
const int FOURTH_GEAR_MAX_SPEED = 90;

const int FIFTH_GEAR_MIN_SPEED = 50;
const int FIFTH_GEAR_MAX_SPEED = MAX_SPEED;

enum class Direction
{
	BACKWARDS = -1,
	STOPPED,
	FORWARD,
};

enum class Gear
{
	REVERSED = MIN_GEAR,
	NEUTRAL,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH,
};

using SpeedInterval = std::pair<int, int>;
using GearsSpeedInterval = std::map<Gear, SpeedInterval>;

const GearsSpeedInterval gearsSpeedIntervals = {
	{ Gear::REVERSED, { REVERSED_GEAR_MIN_SPEED, REVERSED_GEAR_MAX_SPEED } },
	{ Gear::NEUTRAL, { MIN_SPEED, MAX_SPEED } },
	{ Gear::FIRST, { FIRST_GEAR_MIN_SPEED, FIRST_GEAR_MAX_SPEED } },
	{ Gear::SECOND, { SECOND_GEAR_MIN_SPEED, SECOND_GEAR_MAX_SPEED } },
	{ Gear::THIRD, { THIRD_GEAR_MIN_SPEED, FOURTH_GEAR_MAX_SPEED } },
	{ Gear::FOURTH, { FOURTH_GEAR_MIN_SPEED, FOURTH_GEAR_MAX_SPEED } },
	{ Gear::FIFTH, { FIFTH_GEAR_MIN_SPEED, FIFTH_GEAR_MAX_SPEED } }
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


private:
	bool m_isEngineOn;
	int m_speed;
	Gear m_gear;
	Direction m_direction;
};
