#include "DictionaryHandler.h"

int HandleDictionary(std::string inputFilePath, std::istream& input, std::ostream& output)
{
	Dictionaries dictionaries;
	std::fstream inputFile;
	bool isFileMissing = true;

	if (inputFilePath != "")
	{
		inputFile.open(inputFilePath, std::ios_base::in | std::ios_base::app);
		if (!inputFile.is_open())
		{
			output << "���� ������� �� ������� �������." << std::endl;
			return 1;
		}
		isFileMissing = false;
		InitDictionary(inputFile, dictionaries.mainDict);
	}

	bool isWordAdded = false;
	HandleSession(isWordAdded, dictionaries, input, output);

	if (!isWordAdded)
	{
		return 0;
	}

	bool isFileSaved = HandleSavingDictionary(isFileMissing, dictionaries, inputFile, input, output);
	if (!isFileSaved)
	{
		return 1;
	}

	return 0;
}

void InitDictionary(std::istream& inputFile, Dictionary& mainDict)
{
	std::string engWord;
	std::string ruWord;
	while (!inputFile.eof())
	{
		std::getline(inputFile, engWord);
		std::getline(inputFile, ruWord);

		mainDict.emplace(engWord, ruWord);
	}
	inputFile.clear();
}

void HandleSession(bool& isWordAdded, Dictionaries& dictionaries, std::istream& input, std::ostream& output)
{
	bool isRussian = false;
	std::string searchedString;

	while (true)
	{
		std::cout << ">";
		std::getline(std::cin, searchedString);
		isRussian = false;
		searchedString = Trim(searchedString);

		if (searchedString == "...")
		{
			break;
		}
		SwitchIsRussian(searchedString, isRussian);

		if (isRussian)
		{
			searchedString = TransormToLowerCase(searchedString);
		}

		bool isTranslationFound = FindTranslation(isRussian, isWordAdded, dictionaries, searchedString, output);
		if (!isTranslationFound)
		{
			HandleAddingTranslation(searchedString, isRussian, isWordAdded, dictionaries, input, output);
		}
	}
}

std::string Trim(const std::string& string)
{
	std::string str(string);
	str.erase(0, str.find_first_not_of(" \n\r\t"));
	str.erase(str.find_last_not_of(" \n\r\t") + 1);
	return str;
}

void SwitchIsRussian(std::string const& searchedString, bool& isRussian)
{
	if (searchedString[0] >= RUSSIAN_CHARS_UNICODE_START && searchedString[0] <= RUSSIAN_CHARS_UNICODE_END)
	{
		isRussian = true;
	}
}

std::string TransormToLowerCase(std::string& searchedString)
{
	std::string str(searchedString);
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
	return str;
}

void HandleAddingTranslation(std::string& searchedString, bool& isRussian, bool& isWordAdded, Dictionaries& dictionaries, std::istream& input, std::ostream& output)
{
	output << "����������� ����� �" << searchedString << "�. ������� ������� ��� ������ ������ ��� ������." << std::endl;
	std::string translationString;
	output << ">";
	std::getline(input, translationString);

	translationString = TransormToLowerCase(translationString);
	translationString = Trim(translationString);

	if (translationString != "")
	{
		AddTranslation(isWordAdded, isRussian, dictionaries, searchedString, translationString, output);
	}
	else
	{
		output << "����� �" << searchedString << "� ���������������." << std::endl;
	}
}

bool FindTranslation(bool& isRussian, bool& isWordAdded, Dictionaries& dictionaries, std::string& searchedString, std::ostream& output)
{
	bool isFirstTranslationFound = false;
	std::string searchedEl;
	std::string translationEl;

	for (auto el : dictionaries.mainDict)
	{
		if (isRussian)
		{
			searchedEl = el.second;
			translationEl = el.first;
		}
		else
		{
			translationEl = el.second;
			searchedEl = el.first;
		}

		if (searchedEl == searchedString)
		{
			if (isFirstTranslationFound)
			{
				output << ", ";
			}
			output << translationEl;
			isFirstTranslationFound = true;
		}
	}

	if (isFirstTranslationFound)
	{
		output << std::endl;
		return true;
	}
	return false;
}

void AddTranslation(bool& isWordAdded, bool& isRussian, Dictionaries& dictionaries, std::string& searchedString, std::string& translationString, std::ostream& output)
{
	if (isRussian)
	{
		dictionaries.mainDict.emplace(translationString, searchedString);
		dictionaries.sessionDict.emplace(translationString, searchedString);
	}
	else
	{
		dictionaries.mainDict.emplace(searchedString, translationString);
		dictionaries.sessionDict.emplace(searchedString, translationString);
	}
	isWordAdded = true;
	output << "����� �" << searchedString << "� ��������� � ��������� �" << translationString << "�." << std::endl;
}

std::string GetNewDictionaryPath(std::ostream& output)
{
	output << "���� ������� �����������, ������ ������� �����? �������� ���� � ������ ����� ��� N/n ��� ������: " << std::endl
		   << ">";

	std::string newDictionaryFilePath;
	std::getline(std::cin, newDictionaryFilePath);
	if (newDictionaryFilePath == "N" || newDictionaryFilePath == "n")
	{
		output << "��������� �� ���������. �� ��������." << std::endl;
		return "";
	}
	return newDictionaryFilePath;
}

bool HandleSavingDictionary(bool& isFileMissing, Dictionaries& dictionaries, std::ostream& inputFile, std::istream& input, std::ostream& output)
{
	if (isFileMissing)
	{
		std::string newDictionaryFilePath = GetNewDictionaryPath(output);
		if (newDictionaryFilePath == "")
		{
			return true;
		}

		std::ofstream outputFile;
		outputFile.open(newDictionaryFilePath);
		if (!outputFile.is_open())
		{
			output << "����� ���� ������� �� ������� �������." << std::endl;
			return false;
		}

		SaveDictionary(outputFile, dictionaries.sessionDict, isFileMissing, input, output);
	}
	else
	{
		SaveDictionary(inputFile, dictionaries.sessionDict, isFileMissing, input, output);
	}
	return true;
}

void SaveDictionary(std::ostream& outputFile, Dictionary& sessionDict, bool& isFileMissing, std::istream& input, std::ostream& output)
{
	std::string answer;
	if (!isFileMissing)
	{
		output << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
		input >> answer;
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
		output << "��������� ���������. �� ��������." << std::endl;
	}
	else
	{
		output << "��������� �� ���������. �� ��������." << std::endl;
	}
}
