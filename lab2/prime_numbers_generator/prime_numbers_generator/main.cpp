#include <iostream>
#include <set>
#include <vector>

std::set<size_t> GeneratePrimeNumbersSet(size_t upperBound)
{
	std::set<size_t> primesSet;
	std::vector<bool> sieve;
	sieve.assign(upperBound, true);

	for (size_t i = 4; i < sieve.size(); i += 2)
	{
		sieve[i] = false;
	}

	primesSet.insert(2);

	for (size_t i = 3; i < sieve.size(); i += 2)
	{
		if (!sieve[i])
		{
			continue;
		}

		primesSet.emplace(i);

		for (size_t j = i + i * 2; j < sieve.size(); j += i * 2)
		{
			sieve[j] = false;
		}
	}

	return primesSet;
}
int main()
{
	// 100 mils - release
	system("chcp 1251 > nul");
	std::set<size_t> s = GeneratePrimeNumbersSet(100000000);

	std::cout << s.size() << std::endl;

	return 0;
}