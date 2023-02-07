#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int count_of_substrings(string src, string sub) {
	int start = 0;
	int count = 0;
	int pos = 0;
	for (;;) {
		pos = src.find(sub.c_str(), start);
		if (pos != -1) {
			start = pos + sub.size();
			count++;
		}
		else {
			break;
		}
	}
	return count;
}

int main(int argc, char* argv[])
{
	system("chcp 1251 > nul");
	string fileName;
	string substring;

	for (int i = 1; i < argc; i++)
	{
		if (i == 1)
		{
			fileName = argv[1];
		}

		if (i == 2)
		{
			substring = argv[2];
		}
	}
	/*cout << "Filename: " << fileName << endl;
	cout << "SubString: " << substring << endl;*/


	ifstream fIn;
	string text;
	vector<int> vIndex;
	vector<int> vSubstrRepeatition;

	fIn.open(fileName);

	if (fIn.is_open())
	{
		int lineCounter = 1;
		while (!fIn.eof())
		{
			string line = "";
			getline(fIn, line);

			//int index = line.find(substring);
			int index = count_of_substrings(line, substring);

			//cout << index;


			// != -1
			if (index != 0)
			{
				vSubstrRepeatition.push_back(index);
				vIndex.push_back(lineCounter);
			}

			text = text + '\n' + line;
			lineCounter++;
		}
	}
	else
	{
		cout << "Couldn't open the file" << endl;
		return 2;
	}

	if (vIndex.size() == 0)
	{
		cout << "Text not found" << endl;
		return 1;
	}
	else
	{
		cout << "¬хождение строки: " << endl;
		for (int i = 0; i < vIndex.size(); i++)
		{
			if (vSubstrRepeatition[i] != 0)
			{
				cout << vIndex[i] << " -> " << vSubstrRepeatition[i] << " раз" << endl;

			}
			//cout << vIndex[i] << endl;
		}
	}




	return 0;
}