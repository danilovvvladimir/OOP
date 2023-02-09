#include <iostream> 
#include <string> 


std::string numeralSystemSymbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
bool wasError = false;

std::string reverseString(std::string &str)
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

int stringToInt(const std::string& str, int startedNumeralSystem, bool & wasError)
{
	std::string intMaxString = "2147483647";
	std::string intMinString = "-2147483647";

	std::string myString = str;
	if (myString[0] != '-')
	{
		if (intMaxString.size() <= myString.size())
		{
			if (intMaxString < myString)
			{
				wasError = true;
				return 1;
			}

		}
	}
	else
	{
		if (intMinString.size() <= myString.size())
		{
			if (intMinString < myString)
			{
				wasError = true;
				return 2;
			}

		}
	}

	int result = 0;
	int digit[91] = { 0 };



	for (int i = 0; numeralSystemSymbols[i]; i++)
	{
		digit[numeralSystemSymbols[i]] = i;
	}

	for (int i = 0; str[i]; i++)
	{
		if (digit[str[i]] >= startedNumeralSystem || (digit[str[i]] == 0 && (str[i] != '0' && str[i] != '-')))
		{
			wasError = true;
			return 3;
		}
		result = result * startedNumeralSystem + digit[str[i]];
	}

	if (str[0] == '-')
	{
		result = result * -1;
	}


	return result;
}

std::string intToString(int resInt, int finalNumeralSystem, bool & wasError)
{
	std::string result;
	bool isNegative = false;

	if (resInt == 0)
	{
		return "0";
	}

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

void printResult(std::ostream& output, const std::string& strResult)
{
	output << "Final: " <<strResult << "\n";
}



int main(int argc, char* argv[])
{
	// Русские буквы поправить, ограничение только что б английские использовались
	system("chcp 1251 > nul");
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	int startedNumeralSystem = atoi(argv[1]);
	int finalNumeralSystem = atoi(argv[2]);
	std::string value = argv[3];

	int intResult = (stringToInt(value, startedNumeralSystem, wasError));

	if (wasError)
	{
		if (intResult == 1)
		{
			std::cout << "Ошибка. Ввёденное число больше максимально допустимого." << std::endl;
			return 1;
		}
		if (intResult == 2)
		{
			std::cout << "Ошибка. Ввёденное число меньше минимально допустимого." << std::endl;
			return 1;
		}
		if (intResult == 3)
		{
			std::cout << "Ошибка. Это число не входит в данную систему счисления." << std::endl;
			return 1;
		}
		
	}

	std::string strResult = intToString(intResult, finalNumeralSystem, wasError);
	printResult(std::cout, strResult);

	return 0;
}