#include <iostream>
#include <string>

const std::string numeralSystemSymbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
bool wasError = false;

std::string ReverseString(std::string& str)
{
	std::string result = str;
	char temp;
	for (int i = 0; i < static_cast<int>(result.size() / 2); i++)
	{
		temp = result[i];
		result[i] = result[result.size() - 1 - i];
		result[result.size() - 1 - i] = temp;
	}

	return result;
}

int StringToInt(const std::string& str, int startedNumeralSystem, bool& wasError)
{
	int result = 0;
	int digit[91] = { 0 };
	bool isNegative = false;

	for (int i = 0; numeralSystemSymbols[i]; i++)
	{
		digit[numeralSystemSymbols[i]] = i;
	}

	int iter = 0;
	if (str[0] == '-')
	{
		iter = 1;
		isNegative = true;
	}
	for (int i = iter; str[i]; i++)
	{
		if (digit[str[i]] >= startedNumeralSystem || (digit[str[i]] == 0 && (str[i] != '0')) || (int(str[i]) > 90 || int(str[i]) < 48))
		{
			wasError = true;
			return 3;
		}
		if (!isNegative)
		{
			result = result * startedNumeralSystem + digit[str[i]];
		}
		else
		{
			result = result * startedNumeralSystem - digit[str[i]];
		}
	}

	if (str[0] == '-')
	{
		if (result != INT_MIN)
		{
			if (result > 0)
			{
				wasError = true;
				return 2;
			}
		}
	}
	else
	{
		if (result < 0)
		{
			wasError = true;
			return 1;
		}
	}
	return result;
}

std::string IntToString(int resInt, int finalNumeralSystem, bool& wasError)
{
	std::string result;
	bool isNegative = false;
	if (resInt < 0)
	{
		isNegative = true;
	}

	if (resInt == 0)
	{
		return "0";
	}

	while (resInt)
	{
		int tempResInt = resInt % finalNumeralSystem;
		if (isNegative)
		{
			tempResInt *= -1;
		}
		result += numeralSystemSymbols[tempResInt];
		resInt = resInt / finalNumeralSystem;
	}
	if (isNegative)
	{
		result += '-';
	}

	result = ReverseString(result);
	return result;
}

int Radix(std::ostream& output, int srcNotation, int destNotation, std::string value)
{

	if (srcNotation < 2 || srcNotation > 36)
	{
		std::cout << "Notation should be in interval 2-36\n";
		return 1;
	}
	if (destNotation < 2 || destNotation > 36)
	{
		std::cout << "Notation should be in interval 2-36\n";
		return 1;
	}
	int intResult = (StringToInt(value, srcNotation, wasError));
	if (wasError)
	{
		if (intResult == 1)
		{
			std::cout << "Error. Input value is greater than MAX available." << std::endl;
			return 1;
		}
		if (intResult == 2)
		{
			std::cout << "Error. Input value is lesser than MIN available." << std::endl;
			return 1;
		}
		if (intResult == 3)
		{
			std::cout << "Error. Input value is not in Source notation." << std::endl;
			return 1;
		}
	}
	std::string strResult = IntToString(intResult, destNotation, wasError);
	output << strResult << "\n";
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	int statusCode = Radix(std::cout, atoi(argv[1]), atoi(argv[2]), argv[3]);
	if (statusCode != 0)
	{
		return 1;
	}

	return 0;
}
