#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../car/Car.h"
#include <sstream>

SCENARIO("Testing inited Car")
{
	WHEN("When car is created")
	{
		Car car;
		THEN("Direction: stopped, gear: neutral, engine: turned off, speed: 0")
		{
			REQUIRE(car.GetDirection() == Direction::Stopped);
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.GetSpeed() == MIN_SPEED);
			REQUIRE(!car.IsTurnedOn());
		}
	}
}

SCENARIO("Turn ON/OFF engine")
{
	WHEN("Turn ON engine when car is created")
	{
		Car car;
		THEN("Engine is turned ON")
		{
			REQUIRE(!car.IsTurnedOn());
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOn());
		}
	}
	WHEN("Turn ON engine when engine is already turned ON")
	{
		Car car;
		THEN("Engine is turned ON")
		{
			REQUIRE(!car.IsTurnedOn());
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOn());
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOn());
		}
	}
	WHEN("Turn OFF engine when engine is already turned OFF")
	{
		Car car;
		THEN("Engine is turned OFF")
		{
			REQUIRE(!car.IsTurnedOn());
			REQUIRE(car.TurnOffEngine());
			REQUIRE(!car.IsTurnedOn());
		}
	}
	WHEN("Turn ON and then turn OFF engine, when car is created")
	{
		Car car;
		THEN("Engine is turned OFF")
		{
			REQUIRE(!car.IsTurnedOn());
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOn());
			REQUIRE(car.TurnOffEngine());
			REQUIRE(!car.IsTurnedOn());
		}
	}
}