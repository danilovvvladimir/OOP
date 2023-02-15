#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main()
{
	system("chcp 1251 > nul");

	std::multimap<std::string, std::string> dictionary;

	std::fstream inputFile;
	inputFile.open("in.txt");
	while (!inputFile.eof())
	{
		std::string engWord;
		std::getline(inputFile, engWord);
		std::string ruWord;
		std::getline(inputFile, ruWord);
		//std::transform(engWord.begin(), engWord.end(), engWord.begin(), [](unsigned char c) { return tolower(c); });
		//std::transform(ruWord.begin(), ruWord.end(), ruWord.begin(), [](unsigned char c) { return tolower(c); });

		dictionary.emplace(engWord, ruWord);
		dictionary.emplace(ruWord, engWord);
	}
	std::string searchedString;
	bool isWordAdded = false;

	while (searchedString != "...")
	{
		std::getline(std::cin, searchedString);
		if (searchedString == "...")
		{
			break;
		}
		auto it = dictionary.find(searchedString);

		if (it != dictionary.end())
		{
			std::cout << it->second << std::endl;
		}
		else
		{
			std::cout << "Неизвестное слово “" << searchedString << "”. Введите перевод или пустую строку для отказа." << std::endl;
			std::string translationString;
			std::getline(std::cin, translationString);
			if (translationString != "")
			{
				isWordAdded = true;
				dictionary.emplace(searchedString, translationString);
				dictionary.emplace(translationString, searchedString);
			}
			else
			{
				std::cout << "Слово “" << searchedString << "” проигнорировано." << std::endl;
			}
		}
	}
	if (isWordAdded)
	{
		std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
		std::string answer;
		std::cin >> answer;
		if (answer == "Y" || answer == "y")
		{
			inputFile.close();
			inputFile.open("in.txt");

			int counter = 1;
			for (auto mapElement : dictionary)
			{
				if (mapElement.first != "" && mapElement.second != "")
				{
					if (counter % 2 != 0)
					{
						inputFile << mapElement.first << std::endl;
						inputFile << mapElement.second << std::endl;
						counter++;
					}
					else
					{
						counter--;
					}
				}
			}
			std::cout << "Изменения сохранены. До свидания." << std::endl;
		}
		else
		{
			std::cout << "Изменения не сохранены. До свидания." << std::endl;
		}
	}

	return 0;
}