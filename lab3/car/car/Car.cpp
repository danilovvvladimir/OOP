#include "Car.h"

Car::Car()
	: m_isEngineOn(false)
	, m_speed(MIN_SPEED)
	, m_gear(Gear::Neutral)
	, m_direction(Direction::Stopped)
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
		m_direction = Direction::Stopped;
		m_gear = Gear::Neutral;
		m_isEngineOn = true;
	}
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_direction == Direction::Stopped && m_gear == Gear::Neutral)
	{
		m_isEngineOn = false;
		return true;
	}
	return false;
}

bool Car::SetGear(Gear gear)
{
	if (gear == Gear::Neutral)
	{
		// direction сохраняется
		m_gear = gear;
		return true;
	}

	if (gear == Gear::Reversed)
	{
		if (m_direction == Direction::Stopped)
		{
			m_gear = gear;
			m_direction = Direction::Backwards;
			return true;
		}
		else
		{
			return false;
		}
	}

	SpeedInterval speedPair = gearsSpeedIntervals.find(gear)->second;
	if (m_speed >= speedPair.first && m_speed <= speedPair.second && (m_direction == Direction::Stopped || m_direction == Direction::Forwards))
	{
		//
		if (m_direction == Direction::Stopped)
		{
			m_direction = Direction::Forwards;
		}
		m_gear = gear;
		return true;
	}
	return false;
}

bool Car::SetSpeed(int speed)
{
	SpeedInterval speedPair = gearsSpeedIntervals.find(m_gear)->second;
	if (m_gear == Gear::Neutral && (speed >= MIN_SPEED && speed <= m_speed))
	{
		m_speed = speed;
		if (speed == MIN_SPEED)
		{
			m_direction = Direction::Stopped;
		}
		return true;
	}

	if (m_gear != Gear::Neutral && (speed >= speedPair.first && speed <= speedPair.second))
	{
		m_speed = speed;

		if (speed == MIN_SPEED)
		{
			m_direction = Direction::Stopped;
		}
		return true;
	}

	return false;
}

void Car::PrintInfo()
{
	std::cout << "Speed: " << GetSpeed() << std::endl;
	std::cout << "Direction: " << static_cast<int>(GetDirection()) << std::endl;
	std::cout << "Gear: " << static_cast<int>(GetGear()) << std::endl;
	std::cout << "Engine: " << IsTurnedOn() << std::endl;
}
