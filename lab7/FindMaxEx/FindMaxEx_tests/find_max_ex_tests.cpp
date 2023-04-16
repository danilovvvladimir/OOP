#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../FindMaxEx/find_max_ex.hpp"

#include <string>

SCENARIO("Testing with empty vector")
{
	std::vector<size_t> v;

	size_t maxSizet;

	REQUIRE(!FindMax(v, maxSizet, [](size_t firstValue, size_t secondValue) {
		return firstValue < secondValue;
	}));
}

SCENARIO("Testing Function with default types")
{
	WHEN("Testing with size_t")
	{

		std::vector<size_t> v{ 1, 5, 10, 15, 20 };

		size_t maxSizet;

		REQUIRE(FindMax(v, maxSizet, [](size_t firstValue, size_t secondValue) {
			return firstValue < secondValue;
		}));

		REQUIRE(maxSizet == 20);
	}
	WHEN("Testing with double")
	{

		std::vector<double> v{ 1.0001, 5.012, 10.421, 15.0421, 20.001 };

		double maxDouble;

		REQUIRE(FindMax(v, maxDouble, [](double firstValue, double secondValue) {
			return firstValue < secondValue;
		}));

		REQUIRE(maxDouble == 20.001);
	}
	WHEN("Testing with std::string")
	{

		std::vector<std::string> v{ "ea", "ba", "ca", "da", "aa" };

		std::string maxString;

		REQUIRE(FindMax(v, maxString, [](const std::string& firstValue, const std::string& secondValue) {
			return firstValue < secondValue;
		}));

		REQUIRE(maxString == "ea");
	}
}

SCENARIO("Testing with custom class")
{
	class Athlete
	{
	public:
		Athlete() = default;

		Athlete(std::string name, unsigned short height, unsigned short weight)
			: m_name(name)
			, m_height(height)
			, m_weight(weight)
		{
		}

		const std::string& GetName() const { return m_name; }
		unsigned short GetHeight() const { return m_height; }
		unsigned short GetWeight() const { return m_weight; }

	private:
		std::string m_name;
		unsigned short m_height;
		unsigned short m_weight;
	};

	std::vector<Athlete> athletes{
		{ "Danilov Vladimir Vladimirovich", 177, 76 },
		{ "Ivanov Ivan Ivanovich", 165, 66 },
		{ "Vladislavov Vladislav Vladislavovich", 210, 80 },
		{ "Antonov Anton Antonovich", 180, 100 },
	};

	WHEN("Find sportsman with max height")
	{
		Athlete maxHeightAthlete;

		REQUIRE(FindMax(athletes, maxHeightAthlete, [](const Athlete& firstValue, const Athlete& secondValue) {
			return firstValue.GetHeight() < secondValue.GetHeight();
		}));

		REQUIRE(maxHeightAthlete.GetName() == "Vladislavov Vladislav Vladislavovich");
		REQUIRE(maxHeightAthlete.GetHeight() == 210);
		REQUIRE(maxHeightAthlete.GetWeight() == 80);
	}

	WHEN("Find sportsman with max weigth")
	{
		Athlete maxWeightAthlete;

		REQUIRE(FindMax(athletes, maxWeightAthlete, [](const Athlete& firstValue, const Athlete& secondValue) {
			return firstValue.GetWeight() < secondValue.GetWeight();
		}));

		REQUIRE(maxWeightAthlete.GetName() == "Antonov Anton Antonovich");
		REQUIRE(maxWeightAthlete.GetHeight() == 180);
		REQUIRE(maxWeightAthlete.GetWeight() == 100);
	}
}