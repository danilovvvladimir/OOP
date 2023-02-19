#include "GeneratePrimeNumbersSet.h"

std::set<size_t> GeneratePrimeNumbersSet(size_t upperBound)
{
	std::set<size_t> primesSet;
	std::vector<bool> sieve(upperBound + 1, true);

	int sqrtUpperBound = static_cast<int>(round(sqrt(upperBound)));
	sieve[0] = false;
	sieve[1] = false;

	for (size_t i = 2; i <= sqrtUpperBound; i++)
	{
		if (sieve[i])
		{
			for (size_t j = i * i; j <= upperBound; j += i)
			{
				sieve[j] = false;
			}
		}
	}

	for (size_t i = 0; i <= upperBound; i++)
	{
		if (sieve[i])
		{
			primesSet.emplace(i);
		}
	}

	return primesSet;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count" << std::endl
				  << "Usage: prime_numbers_generator.exe <upperBound>" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.upperBound = atoi(argv[1]);
	if (args.upperBound < 2)
	{
		std::cout << "UpperBound should be greater than 1" << std::endl;
		return std::nullopt;
	}

	return args;
}

void PrintPrimeNumbersSet(size_t upperBound, std::ostream& output)
{
	std::set<size_t> primesSet = GeneratePrimeNumbersSet(upperBound);

	for (auto primeNumber : primesSet)
	{
		output << primeNumber << " ";
	}
}