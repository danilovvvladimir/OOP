#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>

using Dictionary = std::multimap<std::string, std::string>;

struct Args
{
	std::string inputFilePath;
};

std::string TransormToLowerCase(bool const isRussian, std::string& searchedString)
{
	std::string str(searchedString);
	if (isRussian)
	{
		std::transform(str.begin(), str.end(), str.begin(), [](char c) {
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
		std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
	}
	return str;
}

std::string Trim(const std::string& source)
{
	std::string s(source);
	s.erase(0, s.find_first_not_of(" \n\r\t"));
	s.erase(s.find_last_not_of(" \n\r\t") + 1);
	return s;
}

void InitDictionary(std::istream& inputFile, Dictionary& enToRuDict, Dictionary& ruToEnDict)
{
	std::string engWord;
	std::string ruWord;
	while (!inputFile.eof())
	{
		std::getline(inputFile, engWord);
		std::getline(inputFile, ruWord);

		enToRuDict.emplace(engWord, ruWord);
		ruToEnDict.emplace(ruWord, engWord);
	}
	inputFile.clear();
}

void SaveDictionary(std::ostream& outputFile, Dictionary& sessionDict, bool& isFileMissing)
{
	std::string answer;

	if (!isFileMissing)
	{
		std::cout << "¬ словарь были внесены изменени€. ¬ведите Y или y дл€ сохранени€ перед выходом." << std::endl;
		std::cin >> answer;
	}
	else
	{
		answer = "Y";
	}

	if (answer == "Y" || answer == "y")
	{
		for (auto dictionaryElement : sessionDict)
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

void AddTranslation(bool& isWordAdded, bool& isRussian, Dictionary& ruToEnDict, Dictionary& enToRuDict, Dictionary& sessionDict, std::string& searchedString, std::string& translationString)
{
	isWordAdded = true;
	if (isRussian)
	{
		ruToEnDict.emplace(searchedString, translationString);
		enToRuDict.emplace(translationString, searchedString);
		sessionDict.emplace(translationString, searchedString);
	}
	else
	{
		enToRuDict.emplace(searchedString, translationString);
		sessionDict.emplace(searchedString, translationString);
		ruToEnDict.emplace(translationString, searchedString);
	}
	std::cout << "—лово У" << searchedString << "Ф добавлено с переводом У" << translationString << "Ф." << std::endl;
}

void FindTranslation(bool& isRussian, bool& isWordAdded, Dictionary& enToRuDict, Dictionary& ruToEnDict, Dictionary& mainDict, Dictionary& sessionDict, std::string& searchedString)
{
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

		translationString = TransormToLowerCase(isRussian, translationString);
		translationString = Trim(translationString);

		if (translationString != "")
		{
			AddTranslation(isWordAdded, isRussian, ruToEnDict, enToRuDict, sessionDict, searchedString, translationString);
		}
		else
		{
			std::cout << "—лово У" << searchedString << "Ф проигнорировано." << std::endl;
		}
	}
}

void HandleDictionary(bool& isWordAdded, Dictionary& enToRuDict, Dictionary& ruToEnDict, Dictionary& mainDict, Dictionary& sessionDict)
{
	bool isRussian = false;
	std::string searchedString;
	while (searchedString != "...")
	{
		isRussian = false;
		std::getline(std::cin, searchedString);
		searchedString = Trim(searchedString);
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

		searchedString = TransormToLowerCase(isRussian, searchedString);

		FindTranslation(isRussian, isWordAdded, enToRuDict, ruToEnDict, mainDict, sessionDict, searchedString);
	}
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc > 2)
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Usage: mini_dictionary.exe <dictionary file name> or mini_dictionary.exe" << std::endl;
		return std::nullopt;
	}

	Args args;
	if (argc == 2)
	{
		args.inputFilePath = argv[1];
	}
	else
	{
		args.inputFilePath = "none";
	}

	return args;
}

int main(int argc, char* argv[])
{
	system("chcp 1251 > nul");

	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	Dictionary enToRuDict;
	Dictionary ruToEnDict;
	Dictionary mainDict;
	Dictionary sessionDict;

	std::fstream inputFile;
	bool isFileMissing = true;

	if (args->inputFilePath != "none")
	{
		inputFile.open(args->inputFilePath, std::ios_base::in | std::ios_base::app);
		if (!inputFile.is_open())
		{
			std::cout << "File is not found" << std::endl;
			return 1;
		}
		isFileMissing = false;
		InitDictionary(inputFile, enToRuDict, ruToEnDict);
	}
	else
	{
		std::cout << "Dictionary file is missing" << std::endl;
	}

	bool isWordAdded = false;
	HandleDictionary(isWordAdded, enToRuDict, ruToEnDict, mainDict, sessionDict);

	if (isWordAdded)
	{
		if (isFileMissing)
		{
			std::cout << "Dictionary file is missing, wanna create new? New dictionary path or write N to cancel:" << std::endl;

			std::string newDictionaryFilePath;
			std::getline(std::cin, newDictionaryFilePath);
			if (newDictionaryFilePath == "N")
			{
				return 1;
			}

			std::ofstream newOutputFile;
			newOutputFile.open(newDictionaryFilePath);

			if (!newOutputFile.is_open())
			{
				std::cout << "Couldn't open new dictionary file" << std::endl;
				return 1;
			}

			SaveDictionary(newOutputFile, sessionDict, isFileMissing);
		}
		else
		{
			SaveDictionary(inputFile, sessionDict, isFileMissing);
		}
	}

	return 0;
}
