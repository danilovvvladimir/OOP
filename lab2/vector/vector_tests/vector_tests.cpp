#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../vector/VectorProcessor.h"
#include <sstream>

SCENARIO("Read vector from istream")
{
	std::vector<double> numbers;
	WHEN("input stream is empty")
	{
		std::istringstream input("");
		THEN("vector is also empty")
		{
			ReadInputToVector(input, numbers);
			REQUIRE(numbers.empty());
			REQUIRE(input.eof());
		}
	}

	WHEN("input stream contains not digits")
	{
		std::istringstream input("hello");
		THEN("Vector is empty")
		{
			ReadInputToVector(input, numbers);
			REQUIRE(numbers.empty());
		}
	}

	WHEN("input stream contains digits and not digits")
	{
		std::istringstream input("3.3 4.4 5hello");
		THEN("Vector contains all numbers before not digit")
		{
			ReadInputToVector(input, numbers);
			REQUIRE(numbers == std::vector<double>{3.3, 4.4, 5.0});
		}
	}

	WHEN("input stream contains 3 double numbers")
	{
		std::istringstream input("4.4 5.5 6.6");
		THEN("vector contains 3 double numbers")
		{
			ReadInputToVector(input, numbers);
			REQUIRE(numbers == std::vector<double>{ 4.4, 5.5, 6.6 });
			REQUIRE(input.eof());
		}
	}

	WHEN("input stream contains 3 double numbers in several lines")
	{
		std::istringstream input("4.4\n 5.5\n 6.6");
		THEN("vector contains 3 double numbers")
		{
			ReadInputToVector(input, numbers);
			REQUIRE(numbers == std::vector<double>{ 4.4, 5.5, 6.6 });
			REQUIRE(input.eof());
		}
	}
}

SCENARIO("Print vector")
{
	std::ostringstream output;
	WHEN("Vector is empty")
	{
		std::vector<double> numbers;
		PrintSortedVector(numbers, output);
		REQUIRE(output.str().empty());
	}
	WHEN("Vector is not sorted")
	{
		std::vector<double> numbers = { 5.5, 2.245, 1.1 };
		PrintSortedVector(numbers, output);
		REQUIRE(output.str() == "1.100 2.245 5.500 ");
	}
	WHEN("Vector is sorted")
	{
		std::vector<double> numbers = { 1.1, 2.245, 5.5 };
		PrintSortedVector(numbers, output);
		REQUIRE(output.str() == "1.100 2.245 5.500 ");
	}
}
SCENARIO("Find min element in vector")
{
	WHEN("Vector contains 3 numbers")
	{
		std::vector<double> numbers = { 1.1, 2.245, 5.5 };
		double minElement = FindMinElementInVector(numbers);
		REQUIRE(minElement == 1.1);
	}
	WHEN("Vector contains 3 negative numbers")
	{
		std::vector<double> numbers = { -1.1, -2.245, -5.5 };
		double minElement = FindMinElementInVector(numbers);
		REQUIRE(minElement == -5.5);
	}
}
SCENARIO("Multiply every element by its min")
{
	WHEN("Vector contains 5 numbers")
	{
		std::vector<double> numbers = { -10.0, 1.1, 3.3, 4.4, 5.5 };
		MultiplyEveryElementByMin(numbers);
		REQUIRE(numbers == std::vector<double>{ 100.0, -11.0, -33.0, -44.0, -55.0 });
	}
	WHEN("Vector is empty")
	{
		std::vector<double> numbers;
		MultiplyEveryElementByMin(numbers);
		REQUIRE(numbers.empty());
	}
}

SCENARIO("Reading input stream, multiply every element by its min and print it in output stream")
{
	std::ostringstream output;
	std::vector<double> numbers;
	WHEN("Input stream contains 5 numbers")
	{
		THEN("Multiply every by its min, sort and print in output stream")
		{
			std::istringstream input("-10.0 1.1 3.3 4.4 5.5");
			ReadInputToVector(input, numbers);
			MultiplyEveryElementByMin(numbers);
			PrintSortedVector(numbers, output);
			REQUIRE(output.str() == "-55.000 -44.000 -33.000 -11.000 100.000 ");
		}
	}
	WHEN("Input stream is empty")
	{
		THEN("Output stream is also empty")
		{
			std::istringstream input("");
			ReadInputToVector(input, numbers);
			MultiplyEveryElementByMin(numbers);
			PrintSortedVector(numbers, output);
			REQUIRE(output.str().empty());
		}
	}
	
}