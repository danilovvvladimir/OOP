#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using Dictionary = std::multimap<std::string, std::string>;

void TransormToLowerCase(bool const isRussian, std::string& searchedString)
{
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
}

void SaveDictionary(std::fstream& outputFile, Dictionary& mainDictionary)
{
	std::cout << "¬ словарь были внесены изменени€. ¬ведите Y или y дл€ сохранени€ перед выходом." << std::endl;

	std::string answer;
	std::cin >> answer;
	if (answer == "Y" || answer == "y")
	{
		outputFile.close();
		outputFile.open("in.txt");

		for (auto dictionaryElement : mainDictionary)
		{
			if (dictionaryElement.first != "" && dictionaryElement.second != "")
			{
				outputFile << dictionaryElement.first << std::endl;
				outputFile << dictionaryElement.second << std::endl;
			}
		}
		std::cout << "»зменени€ сохранены. ƒо свидани€." << std::endl;
	}
	else
	{
		std::cout << "»зменени€ не сохранены. ƒо свидани€." << std::endl;
	}
}

void InitDictionary(std::fstream& inputFile, Dictionary& enToRuDict, Dictionary& ruToEnDict)
{
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
}

void AddTranslation(bool& isWordAdded, bool& isRussian, Dictionary& ruToEnDict, Dictionary& enToRuDict, std::string& searchedString, std::string& translationString)
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
	std::cout << "—лово У" << searchedString << "Ф добавлено с переводом У" << translationString << "Ф." << std::endl;
}

void FindTranslation(bool& isRussian, bool& isWordAdded, Dictionary& enToRuDict, Dictionary& ruToEnDict, Dictionary& mainDict)
{
	std::string searchedString;
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

		TransormToLowerCase(isRussian, searchedString);

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
					break;
				}
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Ќеизвестное слово У" << searchedString << "Ф. ¬ведите перевод или пустую строку дл€ отказа." << std::endl;
			std::string translationString;
			std::getline(std::cin, translationString);

			if (translationString != "")
			{
				AddTranslation(isWordAdded, isRussian, ruToEnDict, enToRuDict, searchedString, translationString);
			}
			else
			{
				std::cout << "—лово У" << searchedString << "Ф проигнорировано." << std::endl;
			}
		}
	}
}

int main()
{
	//trim нужно добавить
	//если входного файла словар€ нет
	system("chcp 1251 > nul");
	Dictionary enToRuDict;
	Dictionary ruToEnDict;
	Dictionary mainDict;

	std::fstream inputFile;
	InitDictionary(inputFile, enToRuDict, ruToEnDict);
	
	
	bool isWordAdded = false;
	bool isRussian = false;

	FindTranslation(isRussian, isWordAdded, enToRuDict, ruToEnDict, mainDict);
	
	if (isWordAdded)
	{
		SaveDictionary(inputFile, enToRuDict);
	}

	return 0;
}
