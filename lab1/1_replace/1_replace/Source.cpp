#include <iostream>
#include <string>
#include <fstream>

int countSubstrings(std::string src, std::string sub) {
	int start = 0;
	int counter = 0;
	int pos = 0;

	while (true)
	{
		pos = src.find(sub.c_str(), start);
		if (pos != -1) {
			start = pos + sub.size();
			counter++;
		}
		else {
			break;
		}
	}
	return counter;
}

std::string replaceSubstring(std::string mainStr, const std::string& searchString, const std::string& replacementString)
{
	std::string strResult = mainStr;
	int searchStringLength = searchString.size();
	int replacementStringLength = replacementString.size();
	int startIndex = 0;
	int substrCounter = countSubstrings(strResult, searchString);

	if (substrCounter > 0)
	{
		for (int k = 0; k < substrCounter; k++)
		{

			std::string strFirstHalf = "";
			std::string strSecondHalf = "";
			int strResultLength = strResult.size();


			int pos = strResult.find(searchString, startIndex);
			startIndex = pos + replacementStringLength;


			for (int i = 0; i < strResultLength; i++)
			{
				if (i < pos)
				{
					strFirstHalf += strResult[i];
				}
				else
				{
					if (i >= pos + searchStringLength)
					{
						strSecondHalf += strResult[i];
					}
				}
			}
			strResult = strFirstHalf + replacementString + strSecondHalf;
		}
	}
	return strResult;
}

void copyStreamWithReplacement(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString)
{
	while (!input.eof())
	{
		std::string line = "";
		std::getline(input, line);
		if (searchString.size() != 0)
		{
			line = replaceSubstring(line, searchString, replacementString);
		}
		output << line << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	std::string searchedSubstring = argv[3];
	std::string replacedSubstring = argv[4];

	std::ifstream inputFile;
	inputFile.open(argv[1]);

	
	if (inputFile.is_open())
	{
		std::ofstream outputFile;
		outputFile.open(argv[2]);
		if (outputFile.is_open())
		{
			copyStreamWithReplacement(inputFile, outputFile, searchedSubstring, replacedSubstring);
			outputFile.flush();
			outputFile.close();
			inputFile.close();
		}
		else
		{
			std::cout << "OUTPUT File couldn't been opened" << std::endl;
			return 1;
		}
	}
	else
	{
		std::cout << "INPUT File couldn't been opened" << std::endl;
		return 1;
	}
	return 0;
}