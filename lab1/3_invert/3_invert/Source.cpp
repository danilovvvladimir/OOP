#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 

using namespace std;

string transformDoubleToStringAndRound(double num)
{
	string result;
	string numStr = to_string(num);
	int length = numStr.size();
	int counter = 0;
	for (int i = 0; i < length; i++)
	{
		if (counter == 4)
		{
			break;
		}
		if (numStr[i] == '.' || counter > 0)
		{
			counter++;
		}
			result += numStr[i];
	}
	return result;
}

int main()
{
	string fInPath = "in.txt";

	ifstream fIn;
	fIn.open(fInPath);

	int matrixIn[3][3];
	string matrixFloatIn[3][3];
	if (fIn.is_open())
	{
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				int tempNumber;
				fIn >> tempNumber;
				matrixIn[i][k] = tempNumber;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				double tempNumber;
				tempNumber = (1.0 / matrixIn[i][k]);
				tempNumber = round(1000 * tempNumber) / 1000.0;
				matrixFloatIn[i][k] = transformDoubleToStringAndRound(tempNumber);
				//matrixFloatIn[i][k] = 1.0 / matrixIn[i][k];
			}
		}


	}
	else
	{
		cout << "Couldn't open the file" << endl;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			cout << matrixIn[i][k] << "\t";
		}
		cout << endl;
	}
	cout << "==============" << endl;

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			cout << matrixFloatIn[i][k] << "\t";
		}
		cout << endl;
	}
	return 0;
}