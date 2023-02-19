#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <optional>

struct Args
{
	size_t upperBound;
};

std::set<size_t> GeneratePrimeNumbersSet(size_t upperBound);
std::optional<Args> ParseArgs(int argc, char* argv[]);
void PrintPrimeNumbersSet(size_t upperBound, std::ostream& output);