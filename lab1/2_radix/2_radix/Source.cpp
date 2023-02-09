#include <iostream> 
#include <string> 

std::string numeralSystemSymbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::string reverseString(std::string &str)
{
	std::string result = str;
	char temp;
	for (int i = 0; i < result.size() / 2; i++)
	{
		temp = result[i];
		result[i] = result[result.size() - 1 - i];
		result[result.size() - 1 - i] = temp;
	}

	return result;
}

//int StringToInt(const string& str, int radix, bool & wasError);
int stringToInt(const std::string& str, int startedNumeralSystem)
{
	int result = 0;
	int digit[91] = { 0 };

	for (int i = 0; numeralSystemSymbols[i]; i++)
	{
		digit[numeralSystemSymbols[i]] = i;
	}

	
	// Иду по всем символам введённой строки и создаю число в десятичной СС, как многочлен.
	for (int i = 0; str[i]; i++)
	{
		result = result * startedNumeralSystem + digit[str[i]];
	}

	if (str[0] == '-')
	{
		result = result * -1;
	}


	return result;
}

//std::string IntToString(int n, int radix, bool & wasError);
std::string intToString(int resInt, int finalNumeralSystem)
{
	std::string result;
	bool isNegative = false;

	if (resInt < 0)
	{
		isNegative = true;
		resInt = resInt * -1;
	}
	while (resInt)
	{
		int tempResInt = resInt % finalNumeralSystem;
		result += numeralSystemSymbols[tempResInt];
		resInt = resInt / finalNumeralSystem;
	}
	if (isNegative)
	{
		result += '-';
	}

	result = reverseString(result);
	return result;
}

int main()
{
	system("chcp 1251 > nul");
	std::string result = "";
	// Проверки на максимальные и минимальные значения (в 16-ричной системе Z быть не может при вводе)
	// wasERROR как в docs при перенаполнении
	int startedNumeralSystem;
	int finalNumeralSystem;
	std::string s;
	std::cout << "startedNumeralSystem: ";
	std::cin >> startedNumeralSystem;
	std::cout << std::endl;
	std::cout << "finalNumeralSystem: ";
	std::cin >> finalNumeralSystem;
	std::cout << std::endl;
	std::cout << "Number: ";
	std::cin >> s;
	std::cout << std::endl;

	int intResult = (stringToInt(s, startedNumeralSystem));
	std::cout << intResult << std::endl;

	std::string strResult = intToString(intResult, finalNumeralSystem);
	std::cout << strResult << std::endl;

	return 0;
}