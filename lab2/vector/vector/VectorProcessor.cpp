#include "VectorProcessor.h"

int ReadInputToVector(std::istream& input, std::vector<double>& outputVector)
{
	std::copy(std::istream_iterator<double>(input), std::istream_iterator<double>(), std::back_inserter(outputVector));
	if (!input.eof())
	{
		std::cout << "Invalid number value." << std::endl;
		return 1;
	}
	return 0;
}

void PrintSortedVector(std::vector<double>& outputVector, std::ostream& output)
{
	const int PRECISION = 3;
	std::sort(outputVector.begin(), outputVector.end());

	output << std::fixed << std::setprecision(PRECISION);
	std::copy(outputVector.begin(), outputVector.end(), std::ostream_iterator<double>(output, " "));
}

double FindMinElementInVector(std::vector<double>& outputVector)
{
	double minElement = INT_MAX;
	std::for_each(outputVector.begin(), outputVector.end(), [&](const double& elem) {
		if (elem < minElement)
		{
			minElement = elem;
		}
	});
	return minElement;
}

void MultiplyEveryElementByMin(std::vector<double>& outputVector)
{
	double minValue = FindMinElementInVector(outputVector);
	std::for_each(outputVector.begin(), outputVector.end(), [&](double& elem) {
		elem *= minValue;
	});
}
