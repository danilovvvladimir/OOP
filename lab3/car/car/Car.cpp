#include "Car.h"

Car::Car()
	: m_isEngineOn(false)
	, m_speed(MIN_SPEED)
	, m_gear(Gear::NEUTRAL)
	, m_direction(Direction::STOPPED)
{
}

Direction Car::GetDirection() const
{
	return m_direction;
}

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
}

int Car::GetSpeed() const
{
	return m_speed;
}

Gear Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	if (!m_isEngineOn)
	{
		m_direction = Direction::STOPPED;
		m_gear = Gear::NEUTRAL;
		m_isEngineOn = true;
	}
	return true;
}

bool Car::TurnOffEngine()
{
	if (!m_isEngineOn)
	{
		return true;
	}

	if (m_direction == Direction::STOPPED && m_gear == Gear::NEUTRAL)
	{
		m_isEngineOn = false;
		return true;
	}
	return false;
}

bool Car::SetGear(Gear gear)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	if (gear == Gear::NEUTRAL)
	{
		m_gear = gear;
		return true;
	}

	if (gear == Gear::REVERSED)
	{
		if (m_direction != Direction::STOPPED)
		{
			return false;
		}

		m_gear = gear;
		return true;
	}

	SpeedInterval newGearSpeedInterval = gearsSpeedIntervals.find(gear)->second;
	bool isSpeedOkForNewGear = (m_speed >= newGearSpeedInterval.first && m_speed <= newGearSpeedInterval.second);

	if (isSpeedOkForNewGear)
	{
		m_gear = gear;
		return true;
	}
	return false;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	SpeedInterval currentGearSpeedInterval = gearsSpeedIntervals.find(m_gear)->second;
	bool isGearNeutral = (m_gear == Gear::NEUTRAL);
	bool isSpeedOKforNeutral = (speed >= MIN_SPEED && speed <= m_speed);
	bool isSpeedOKforNotNeutral = (speed >= currentGearSpeedInterval.first && speed <= currentGearSpeedInterval.second);

	if ((isGearNeutral && isSpeedOKforNeutral) || (!isGearNeutral && isSpeedOKforNotNeutral))
	{
		m_speed = speed;

		if (m_direction == Direction::STOPPED && (m_gear != Gear::REVERSED && !isGearNeutral))
		{
			m_direction = Direction::FORWARD;
		}

		if (m_direction == Direction::STOPPED && m_gear == Gear::REVERSED)
		{
			m_direction =  Direction::BACKWARDS;
		}

		if (speed == MIN_SPEED)
		{
			m_direction = Direction::STOPPED;
		}

		return true;
	}

	return false;
}
