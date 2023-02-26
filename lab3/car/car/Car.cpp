#include "Car.h"

int Car::GetDirection() const
{
	return 0;
}

Car::Car()
	: m_isEngineOn(false)
	, m_speed(MIN_SPEED)
	, m_gear(0)
{
}

bool Car::IsTurnedOn() const
{
	return false;
}

int Car::GetSpeed() const
{
	return 0;
}

int Car::GetGear() const
{
	return 0;
}

bool Car::TurnOnEngine()
{
	return false;
}

bool Car::TurnOffEngine()
{
	return false;
}

bool Car::SetGear(int gear)
{
	return false;
}

bool Car::SetSpeed(int speed)
{
	return false;
}
