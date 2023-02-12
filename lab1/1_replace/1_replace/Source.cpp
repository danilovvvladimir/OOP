#include <fstream>
#include <iostream>
#include <string>

int CountSubstrings(std::string& src, std::string sub)
{
	int startIndex = 0;
	int counterSubstr = 0;
	int pos = 0;

	while (true)
	{
		pos = src.find(sub.c_str(), startIndex);
		if (pos != -1)
		{
			startIndex = pos + sub.size();
			counterSubstr++;
		}
		else
		{
			break;
		}
	}
	return counterSubstr;
}

std::string ReplaceSubstring(const std::string& mainStr, const std::string& searchString, const std::string& replacementString)
{
	std::string strResult = mainStr;
	int searchStringLength = searchString.size();
	int replacementStringLength = replacementString.size();
	int startIndex = 0;
	int substrCounter = CountSubstrings(strResult, searchString);

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

void CopyStreamWithReplacement(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString)
{
	while (!input.eof())
	{
		std::string line = "";
		std::getline(input, line);
		if (searchString.size() != 0)
		{
			line = ReplaceSubstring(line, searchString, replacementString);
		}
		output << line << std::endl;
	}
}

int CopyFileWithReplacement(std::string inputFileName, std::string outputFileName, std::string searchedStr, std::string replacedStr)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);

	if (inputFile.is_open())
	{
		std::ofstream outputFile;
		outputFile.open(outputFileName);
		if (outputFile.is_open())
		{
			CopyStreamWithReplacement(inputFile, outputFile, searchedStr, replacedStr);
			outputFile.flush();
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

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	int statusCode = CopyFileWithReplacement(argv[1], argv[2], argv[3], argv[4]);
	if (statusCode != 0)
	{
		return 1;
	}
	

	return 0;
}
