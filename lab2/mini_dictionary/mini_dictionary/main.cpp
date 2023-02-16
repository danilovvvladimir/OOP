#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main()
{
	//trim ����� ��������
	system("chcp 1251 > nul");
	std::multimap<std::string, std::string> enToRuDict;
	std::multimap<std::string, std::string> ruToEnDict;
	std::multimap<std::string, std::string> mainDict;

	std::fstream inputFile;
	inputFile.open("in.txt");
	while (!inputFile.eof())
	{
		std::string engWord;
		std::getline(inputFile, engWord);
		std::string ruWord;
		std::getline(inputFile, ruWord);

		enToRuDict.emplace(engWord, ruWord);
		ruToEnDict.emplace(ruWord, engWord);
	}
	std::string searchedString;
	bool isWordAdded = false;

	bool isRussian = false;
	while (searchedString != "...")
	{
		isRussian = false;
		std::getline(std::cin, searchedString);

		if (searchedString == "...")
		{
			break;
		}

		if (searchedString[0] > -65 && searchedString[0] < 0)
		{
			isRussian = true;
			mainDict = ruToEnDict;
		}
		else
		{
			mainDict = enToRuDict;
		}

		if (isRussian)
		{
			std::transform(searchedString.begin(), searchedString.end(), searchedString.begin(), [](char c) {
				if (c < -32)
				{
					return char(int(c + 32));
				}
				else
				{
					return c;
				}
			});
		}
		else
		{
			std::transform(searchedString.begin(), searchedString.end(), searchedString.begin(), [](unsigned char c) { return tolower(c); });
		}

		auto it = mainDict.find(searchedString);

		if (it != mainDict.end())
		{
			auto it = mainDict.find(searchedString);
			int counter = 0;
			while (it != mainDict.end())
			{
				if (it->first == searchedString)
				{
					if (counter > 0)
					{
						std::cout << ", ";
					}
					std::cout << it->second;
					it++;
					counter++;
				}
				else
				{
					std::cout << std::endl;
					break;
				}
			}
		}
		else
		{
			std::cout << "����������� ����� �" << searchedString << "�. ������� ������� ��� ������ ������ ��� ������." << std::endl;
			std::string translationString;
			std::getline(std::cin, translationString);
			if (translationString != "")
			{
				isWordAdded = true;
				if (isRussian)
				{
					ruToEnDict.emplace(searchedString, translationString);
					enToRuDict.emplace(translationString, searchedString);
				}
				else
				{
					enToRuDict.emplace(searchedString, translationString);
					ruToEnDict.emplace(translationString, searchedString);
				}
				std::cout << "����� �" << searchedString << "� ��������� � ��������� �" << translationString << "�." << std::endl;
			}
			else
			{
				std::cout << "����� �" << searchedString << "� ���������������." << std::endl;
			}
		}
	}
	if (isWordAdded)
	{
		std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
		std::string answer;
		std::cin >> answer;
		if (answer == "Y" || answer == "y")
		{
			inputFile.close();
			inputFile.open("in.txt");

			for (auto mapElement : enToRuDict)
			{
				if (mapElement.first != "" && mapElement.second != "")
				{
					inputFile << mapElement.first << std::endl;
					inputFile << mapElement.second << std::endl;
				}
			}
			std::cout << "��������� ���������. �� ��������." << std::endl;
		}
		else
		{
			std::cout << "��������� �� ���������. �� ��������." << std::endl;
		}
	}

	return 0;
}
