#include "VectorProcessor.h"

int main()
{
	std::vector<double> numbers;
	int statusCode = ReadInputToVector(std::cin, numbers);

	if (statusCode != 0)
	{
		return 1;
	}

	MultiplyEveryElementByMin(numbers);
	PrintSortedVector(numbers, std::cout);

	return 0;
}
