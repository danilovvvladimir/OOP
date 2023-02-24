#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CTVSet/CTVSet.h"
#include <sstream>

SCENARIO("Init TV")
{
	WHEN("TV is inited")
	{
		CTVSet tv;
		THEN("TV is not working and currentChannel is 0")
		{
			REQUIRE(!tv.IsTurnedOn());
			REQUIRE(tv.GetChannel() == TURNED_OFF_CHANNEL);
		}
	}
	WHEN("TV is turned OFF when its already turned off")
	{
		CTVSet tv;
		THEN("TV is not working and currentChannel is 0")
		{
			REQUIRE(!tv.TurnOff());
			REQUIRE(!tv.IsTurnedOn());
			REQUIRE(tv.GetChannel() == TURNED_OFF_CHANNEL);
		}
	}
	WHEN("TV is turned ON , when its already turned ON for the first time")
	{
		CTVSet tv;
		THEN("TV is not working and currentChannel is INIT_STARTED_CHANNEL")
		{
			REQUIRE(tv.TurnOn());
			REQUIRE(!tv.TurnOn());
			REQUIRE(tv.IsTurnedOn());
			REQUIRE(tv.GetChannel() == INIT_STARTED_CHANNEL);
		}
	}
	WHEN("TV is turned on for the first time")
	{
		CTVSet tv;
		THEN("TV is working and currentChannel is INIT_STARTED_CHANNEL")
		{
			tv.TurnOn();
			REQUIRE(tv.IsTurnedOn());
			REQUIRE(tv.GetChannel() == INIT_STARTED_CHANNEL);
		}
	}
}

SCENARIO("Select channel")
{
	WHEN("TV is turned on and channel is changed to available value(10)")
	{
		CTVSet tv;
		THEN("TV is working and currentChannel is 10")
		{
			REQUIRE(tv.TurnOn());
			REQUIRE(tv.IsTurnedOn());
			REQUIRE(tv.SelectChannel(10));
			REQUIRE(tv.GetChannel() == 10);
		}
	}
	WHEN("TV is turned on and channel is changed to unavailable value(100)")
	{
		CTVSet tv;
		THEN("TV is working and currentChannel is startedChannel(1)")
		{
			REQUIRE(tv.TurnOn());
			REQUIRE(tv.IsTurnedOn());
			REQUIRE(!tv.SelectChannel(100));
			REQUIRE(tv.GetChannel() == INIT_STARTED_CHANNEL);
		}
	}
	WHEN("TV is turned ON and channel is changed to available value(10), then tv is turned OFF and turned ON")
	{
		CTVSet tv;
		THEN("TV is working and currentChannel is the same channel, when tv has been turned OFF")
		{
			REQUIRE(tv.TurnOn());
			REQUIRE(tv.IsTurnedOn());
			REQUIRE(tv.SelectChannel(10));
			REQUIRE(tv.GetChannel() == 10);
			REQUIRE(tv.TurnOff());
			REQUIRE(tv.GetChannel() == 0);
			REQUIRE(tv.TurnOn());
			REQUIRE(tv.GetChannel() == 10);
		}
	}
}

SCENARIO("Previous channel")
{
	WHEN("Tv is turned ON, selected channel 25, then selected channel 50 and selected previous channel")
	{
		CTVSet tv;
		THEN("current channel is 25")
		{
			REQUIRE(tv.TurnOn());
			REQUIRE(tv.IsTurnedOn());
			REQUIRE(tv.SelectChannel(25));
			REQUIRE(tv.SelectChannel(50));
			REQUIRE(tv.SelectPreviousChannel());
			REQUIRE(tv.GetChannel() == 25);
		}
	}
}
