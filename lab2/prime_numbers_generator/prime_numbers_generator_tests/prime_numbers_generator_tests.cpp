#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../prime_numbers_generator/GeneratePrimeNumbersSet.h"
#include <sstream>

SCENARIO("Fill set with prime numbers in interval")
{
	std::set<size_t> expectedPrimeNumbersSet;
	WHEN("UpperBound is lesser than 2")
	{
		THEN("Result SET will be empty")
		{
			expectedPrimeNumbersSet = GeneratePrimeNumbersSet(1);
			REQUIRE(expectedPrimeNumbersSet.empty());
		}
	}
	WHEN("UpperBound is 10")
	{
		THEN("Result SET will be 2, 3, 5, 7")
		{
			expectedPrimeNumbersSet = GeneratePrimeNumbersSet(10);
			REQUIRE(expectedPrimeNumbersSet == std::set<size_t>{ 2, 3, 5, 7 });
		}
	}
	WHEN("UpperBound is 100 mils")
	{
		THEN("Result SET's size will be 5761455")
		{
			expectedPrimeNumbersSet = GeneratePrimeNumbersSet(100000000);
			REQUIRE(expectedPrimeNumbersSet.size() == 5761455);
		}
	}
}