#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

int bin2dec(string binNumber)
{
	int length = binNumber.size();
	int result = 0;
	for (int i = 0; i < length; i++)
	{
		if (binNumber[i] != '0' && binNumber[i] != '1')
		{
			return -1;
		}
		int tempNumber = binNumber[i] - '0';
		result += pow(2, (length - 1 - i)) *tempNumber;

	}
	return result;
}

int main(int argc, char* argv[])
{
	string binNumberStr = argv[1];

	int decNumber = bin2dec(binNumberStr);
	if (decNumber == -1)
	{
		cout << "CHECK NUMBER" << endl;
	}
	else
	{
		cout << decNumber;

	}

	return 0;
}