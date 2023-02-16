#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <iomanip>

const int PRECISION = 3;

int ReadInput(std::istream& input, std::vector<double>& outputVector)
{
	std::copy(std::istream_iterator<double>(input), std::istream_iterator<double>(), std::back_inserter(outputVector));
	/*if (!std::cin.eof())
	{
		std::cout << "Invalid number value was found" << std::endl;
		return 1;
	}*/
	return 0;
}

void PrintSortedVector(std::vector<double>& outputVector, std::ostream& output)
{
	std::sort(outputVector.begin(), outputVector.end());

	output << std::fixed << std::setprecision(PRECISION);
	std::copy(outputVector.begin(), outputVector.end(), std::ostream_iterator<double>(std::cout, " "));
}

int main()
{
	std::vector<double> numbers;
	int statusCode = ReadInput(std::cin, numbers);

	if (statusCode != 0)
	{
		return 1;
	}

	PrintSortedVector(numbers, std::cout);

	return 0;
}