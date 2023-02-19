#include "DictionaryHandler.h"

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
	std::string str(source);
	str.erase(0, str.find_first_not_of(" \n\r\t"));
	str.erase(str.find_last_not_of(" \n\r\t") + 1);
	return str;
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
		bool isFirstTranslationSkipped = false;

		while (it != mainDict.end())
		{
			if (it->first == searchedString)
			{
				if (isFirstTranslationSkipped && it->second != "")
				{
					std::cout << ", ";
				}

				std::cout << it->second;
				it++;
				isFirstTranslationSkipped = true;
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

void HandleSession(bool& isWordAdded, Dictionary& enToRuDict, Dictionary& ruToEnDict, Dictionary& mainDict, Dictionary& sessionDict)
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
		args.inputFilePath = "";
	}

	return args;
}

bool isFileOpened(std::fstream& file)
{
	if (!file.is_open())
	{
		std::cout << "‘айл не найден." << std::endl;
		return false;
	}
	return true;
}

int HandleDictionary(std::string inputFilePath)
{
	Dictionary enToRuDict, ruToEnDict, mainDict, sessionDict;
	std::fstream inputFile;
	bool isFileMissing = true;

	if (inputFilePath != "")
	{
		inputFile.open(inputFilePath, std::ios_base::in | std::ios_base::app);
		if (!isFileOpened(inputFile))
		{
			return 1;
		}
		isFileMissing = false;
		InitDictionary(inputFile, enToRuDict, ruToEnDict);
	}

	bool isWordAdded = false;
	HandleSession(isWordAdded, enToRuDict, ruToEnDict, mainDict, sessionDict);

	if (isWordAdded)
	{
		if (isFileMissing)
		{
			std::cout << "‘айл словар€ отсутствует, хотите создать новый? Ќапишите путь к новому файлу или N дл€ выхода: " << std::endl << ">";

			std::string newDictionaryFilePath;
			std::getline(std::cin, newDictionaryFilePath);
			if (newDictionaryFilePath == "N")
			{
				return 1;
			}

			std::fstream newOutputFile;
			newOutputFile.open(newDictionaryFilePath, std::ios_base::out);
			if (!isFileOpened(newOutputFile))
			{
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