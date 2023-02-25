#include "DictionaryHandler.h"

std::string TransormToLowerCase(bool const isRussian, std::string& searchedString)
{
	std::string str(searchedString);
	if (isRussian)
	{
		std::transform(str.begin(), str.end(), str.begin(), [](char c) {
			if (c < RUSSIAN_BIG_CHARS_UNICODE_END)
			{
				return char(int(c + RUSSIAN_BIG_TO_SMALL_CHARS_CODE));
			}
			return c;
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

void InitDictionary(std::istream& inputFile, Dictionaries& dictionaries)
{
	std::string engWord;
	std::string ruWord;
	while (!inputFile.eof())
	{
		std::getline(inputFile, engWord);
		std::getline(inputFile, ruWord);

		dictionaries.enToRuDict.emplace(engWord, ruWord);
		dictionaries.ruToEnDict.emplace(ruWord, engWord);
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

void AddTranslation(bool& isWordAdded, bool& isRussian, Dictionaries& dictionaries, std::string& searchedString, std::string& translationString)
{
	isWordAdded = true;
	if (isRussian)
	{
		dictionaries.ruToEnDict.emplace(searchedString, translationString);
		dictionaries.enToRuDict.emplace(translationString, searchedString);
		dictionaries.sessionDict.emplace(translationString, searchedString);
	}
	else
	{
		dictionaries.enToRuDict.emplace(searchedString, translationString);
		dictionaries.sessionDict.emplace(searchedString, translationString);
		dictionaries.ruToEnDict.emplace(translationString, searchedString);
	}
	std::cout << "—лово У" << searchedString << "Ф добавлено с переводом У" << translationString << "Ф." << std::endl;
}

void FindTranslation(bool& isRussian, bool& isWordAdded, Dictionaries& dictionaries, std::string& searchedString)
{
	auto it = dictionaries.currentDict.find(searchedString);

	if (it != dictionaries.currentDict.end())
	{
		auto it = dictionaries.currentDict.find(searchedString);
		bool isFirstTranslationSkipped = false;

		while (it != dictionaries.currentDict.end())
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
			AddTranslation(isWordAdded, isRussian, dictionaries, searchedString, translationString);
		}
		else
		{
			std::cout << "—лово У" << searchedString << "Ф проигнорировано." << std::endl;
		}
	}
}

void HandleSession(bool& isWordAdded, Dictionaries& dictionaries)
{
	bool isRussian = false;
	std::string searchedString;

	while (std::getline(std::cin, searchedString))
	{
		isRussian = false;
		searchedString = Trim(searchedString);
		if (searchedString == "...")
		{
			break;
		}

		SwitchCurrentDict(searchedString, isRussian, dictionaries);

		searchedString = TransormToLowerCase(isRussian, searchedString);
		FindTranslation(isRussian, isWordAdded, dictionaries, searchedString);
	}
}

void SwitchCurrentDict(std::string const& searchedString, bool& isRussian, Dictionaries& dictionaries)
{
	if (searchedString[0] >= RUSSIAN_CHARS_UNICODE_START && searchedString[0] <= RUSSIAN_CHARS_UNICODE_END)
	{
		isRussian = true;
		dictionaries.currentDict = dictionaries.ruToEnDict;
	}
	else
	{
		dictionaries.currentDict = dictionaries.enToRuDict;
	}
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
	Dictionaries dictionaries;
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
		InitDictionary(inputFile, dictionaries);
	}

	bool isWordAdded = false;
	HandleSession(isWordAdded, dictionaries);

	if (isWordAdded)
	{
		if (isFileMissing)
		{
			std::cout << "‘айл словар€ отсутствует, хотите создать новый? Ќапишите путь к новому файлу или N/n дл€ выхода: " << std::endl
					  << ">";

			std::string newDictionaryFilePath;
			std::getline(std::cin, newDictionaryFilePath);
			if (newDictionaryFilePath == "N" || newDictionaryFilePath == "n")
			{
				return 0;
			}

			std::fstream newOutputFile;
			newOutputFile.open(newDictionaryFilePath, std::ios_base::out);
			if (!isFileOpened(newOutputFile))
			{
				return 1;
			}
			SaveDictionary(newOutputFile, dictionaries.sessionDict, isFileMissing);
		}
		else
		{
			SaveDictionary(inputFile, dictionaries.sessionDict, isFileMissing);
		}
	}
	return 0;
}