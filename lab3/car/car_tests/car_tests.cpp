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

SCENARIO("Test set gear")
{
	WHEN("Engine is turned OFF and switch gear")
	{
		Car car;
		THEN("Gear is still neutral")
		{
			REQUIRE(!car.IsTurnedOn());
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(!car.SetGear(Gear::Fifth));
			REQUIRE(car.GetGear() == Gear::Neutral);
		}
	}
	WHEN("Engine is turned ON and switch gear to first")
	{
		Car car;
		THEN("Gear is first")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOn());
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.SetGear(Gear::First));
			REQUIRE(car.GetGear() == Gear::First);
		}
	}
	WHEN("Engine is turned ON and switch gear to reversed")
	{
		Car car;
		THEN("Gear is reversed")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOn());
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.SetGear(Gear::Reversed));
			REQUIRE(car.GetGear() == Gear::Reversed);
		}
	}
	WHEN("Engine is turned ON and switch gear to second")
	{
		Car car;
		THEN("Gear is still neutral")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOn());
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(!car.SetGear(Gear::Second));
			REQUIRE(car.GetGear() == Gear::Neutral);
		}
	}
}

SCENARIO("Test set speed")
{
	WHEN("Set speed to 10, when engine is turned OFF")
	{
		Car car;
		THEN("speed is 0")
		{
			REQUIRE(!car.IsTurnedOn());
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(!car.SetSpeed(10));
			REQUIRE(car.GetSpeed() == 0);
		}
	}
	WHEN("Set speed to 10, when engine is turned ON and gear is neutral")
	{
		Car car;
		THEN("speed is 0")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOn());
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(!car.SetSpeed(10));
			REQUIRE(car.GetSpeed() == 0);
		}
	}
	WHEN("Set speed to 10, when engine is turned ON and gear is first")
	{
		Car car;
		THEN("speed is 10")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOn());
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.SetGear(Gear::First));
			REQUIRE(car.SetSpeed(10));
			REQUIRE(car.GetSpeed() == 10);
			REQUIRE(car.GetGear() == Gear::First);
		}
	}
	WHEN("Set speed to unavailable value for current gear")
	{
		Car car;
		THEN("speed is the same")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear(Gear::First));
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(!car.SetSpeed(31));
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetGear() == Gear::First);
		}
	}
}

SCENARIO("Combined testing")
{
	WHEN("Speed up to 150 correctly: first -> second -> fifth gears")
	{
		Car car;
		THEN("gear is fifth, speed it 150")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.SetGear(Gear::First));
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.SetGear(Gear::Second));
			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.GetSpeed() == 50);
			REQUIRE(car.SetGear(Gear::Fifth));
			REQUIRE(car.SetSpeed(150));
			REQUIRE(car.GetSpeed() == 150);
		}
	}
	WHEN("Speed down from 150(forward) to 20(backward) correctly: fifth -> second -> first(speed == 0) -> reversed gear")
	{
		Car car;
		THEN("gear is fifth, speed it 150")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.SetGear(Gear::First));
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.SetGear(Gear::Second));
			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.GetSpeed() == 50);
			REQUIRE(car.SetGear(Gear::Fifth));
			REQUIRE(car.SetSpeed(150));
			REQUIRE(car.GetSpeed() == 150);
			REQUIRE(car.GetDirection() == Direction::Forwards);

			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.SetGear(Gear::Second));
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.SetGear(Gear::First));
			REQUIRE(car.SetSpeed(0));
			REQUIRE(car.GetDirection() == Direction::Stopped);
			REQUIRE(car.SetGear(Gear::Reversed));
			REQUIRE(car.SetSpeed(20));
			REQUIRE(car.GetDirection() == Direction::Backwards);
		}
	}
}


SCENARIO("Complicated testing")
{
	WHEN("Car is stopped, switch to Reversed Gear")
	{
		Car car;
		THEN("Direction is reversed")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetDirection() == Direction::Stopped);

			REQUIRE(car.SetGear(Gear::Reversed));
			REQUIRE(car.GetDirection() == Direction::Backwards);
		}
	}

	WHEN("Car is moving forward, switch to Reversed Gear")
	{
		Car car;
		THEN("Direction is forward, gear is still first")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.GetDirection() == Direction::Stopped);
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.SetGear(Gear::First));
			REQUIRE(car.SetSpeed(1));
			REQUIRE(car.GetDirection() == Direction::Forwards);

			REQUIRE(!car.SetGear(Gear::Reversed));
			REQUIRE(car.GetGear() == Gear::First);
			REQUIRE(car.GetDirection() == Direction::Forwards);
		}
	}

	WHEN("Car is moving backward at neutral gear, switch to Reversed Gear")
	{
		Car car;
		THEN("Direction is still backwars, gear is neutral")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.GetDirection() == Direction::Stopped);
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.SetGear(Gear::Reversed));
			REQUIRE(car.SetSpeed(1));
			REQUIRE(car.GetDirection() == Direction::Backwards);
			REQUIRE(car.SetGear(Gear::Neutral));
			REQUIRE(car.GetGear() == Gear::Neutral);

			REQUIRE(!car.SetGear(Gear::Reversed));
			REQUIRE(car.GetGear() == Gear::Neutral);
		}
	}

	WHEN("Switch from reversed gear to first one correctly")
	{
		Car car;
		THEN("Direction is still backwards, gear is neutral")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.SetGear(Gear::Reversed));
			REQUIRE(car.SetSpeed(10));
			REQUIRE(car.GetDirection() == Direction::Backwards);

			REQUIRE(car.SetSpeed(0));
			REQUIRE(car.SetGear(Gear::First));
			REQUIRE(car.GetGear() == Gear::First);
			REQUIRE(car.GetDirection() == Direction::Forwards);
		}
	}
}