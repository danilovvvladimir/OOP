#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Date/CDate.h"

SCENARIO("Testing CDate initialization ")
{
	WHEN("Inited with min timestamp")
	{
		THEN("Date is 01.01.1970")
		{
			CDate date(0);
			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == MIN_AVAILABLE_YEAR);
		}
	}
	WHEN("Inited with max timestamp")
	{
		THEN("Date is 01.01.9999")
		{
			CDate date(MAX_AVAILABLE_DAY);
			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == MAX_AVAILABLE_YEAR);
		}
	}
	WHEN("Inited with min available date values")
	{
		THEN("Date is 01.01.1970")
		{
			CDate date(1, Month::JANUARY, MIN_AVAILABLE_YEAR);
			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == MIN_AVAILABLE_YEAR);
		}
	}
	WHEN("Inited with max available date values")
	{
		THEN("Date is 01.01.9999")
		{
			CDate date(1, Month::JANUARY, MAX_AVAILABLE_YEAR);
			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == MAX_AVAILABLE_YEAR);
		}
	}
	WHEN("Inited with random date values")
	{
		THEN("Date is 20.03.2023")
		{
			CDate date(20, Month::MARCH, 2023);
			REQUIRE(date.GetDay() == 20);
			REQUIRE(date.GetMonth() == Month::MARCH);
			REQUIRE(date.GetYear() == 2023);
		}
	}
}

SCENARIO("Testing isValid")
{
	WHEN("Date is valid")
	{
		CDate date(20, Month::MARCH, 2023);
		REQUIRE(date.IsValid());
	}
	WHEN("Date is not valid (date min value - 1)")
	{
		CDate date(31, Month::DECEMBER, MIN_AVAILABLE_YEAR - 1);
		REQUIRE(!date.IsValid());
	}
	WHEN("Date is not valid (date max value + 1)")
	{
		CDate date(2, Month::JANUARY, MAX_AVAILABLE_YEAR);
		REQUIRE(!date.IsValid());
	}
}

SCENARIO("Testing Date Values Getters")
{
	Days testDay = 20;
	Month testMonth = Month::MARCH;
	Year testYear = 2023;

	CDate date(testDay, testMonth, testYear);
	WHEN("Get Day")
	{
		THEN("Day is equal to testDay")
		{
			REQUIRE(date.GetDay() == testDay);
		}
	}
	WHEN("Get Month")
	{
		THEN("Month is equal to testMonth")
		{
			REQUIRE(date.GetMonth() == testMonth);
		}
	}
	WHEN("Get Year")
	{
		THEN("Year is equal to testYear")
		{
			REQUIRE(date.GetYear() == testYear);
		}
	}
}

SCENARIO("Testing Get WeekDay")
{
	WHEN("Weekday is Monday")
	{
		CDate date(20, Month::MARCH, 2023);
		REQUIRE(date.GetWeekDay() == WeekDay::MONDAY);
	}
}