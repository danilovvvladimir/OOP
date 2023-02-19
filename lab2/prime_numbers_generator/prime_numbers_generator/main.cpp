#include "GeneratePrimeNumbersSet.h"

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	PrintPrimeNumbersSet(args->upperBound, std::cout);

	return 0;
}
