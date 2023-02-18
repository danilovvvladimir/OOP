#pragma once
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

int ReadInputToVector(std::istream& input, std::vector<double>& outputVector);
void PrintSortedVector(std::vector<double>& outputVector, std::ostream& output);
double FindMinElementInVector(std::vector<double>& outputVector);
void MultiplyEveryElementByMin(std::vector<double>& outputVector);