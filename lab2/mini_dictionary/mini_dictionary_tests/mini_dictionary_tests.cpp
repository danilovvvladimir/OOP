#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../mini_dictionary/DictionaryHandler.h"
#include <sstream>

SCENARIO("Test inited dictionaries")
{
	WHEN("dictionary is empty")
	{
		Dictionaries dictionaries;
		THEN("final dictionary is empty")
		{
			REQUIRE(dictionaries.mainDict.empty());
		}
	}
	WHEN("IStream is word with translation")
	{
		Dictionaries dictionaries;
		std::istringstream input("cat\nкошка");
		THEN("Dictionary contains 1 pair")
		{
			InitDictionary(input, dictionaries.mainDict);
			REQUIRE(dictionaries.mainDict.size() == 1);
			REQUIRE(dictionaries.mainDict == std::multimap<std::string, std::string>{ { "cat", "кошка" } });
		}
	}
	WHEN("IStream is 2 words with translations")
	{
		Dictionaries dictionaries;
		std::istringstream input("cat\nкошка\ndog\nсобака");
		THEN("Dictionary contains 2 pairs")
		{
			InitDictionary(input, dictionaries.mainDict);
			REQUIRE(dictionaries.mainDict.size() == 2);
			REQUIRE(dictionaries.mainDict == std::multimap<std::string, std::string>{ { "cat", "кошка" }, { "dog", "собака" } });
		}
	}
}

SCENARIO("Test SwitchIsRussian")
{
	WHEN("Word is russian")
	{
		bool isRussian = false;
		std::string str = "–усска€ лексема";
		THEN("isRussian is true")
		{
			SwitchIsRussian(str, isRussian);
			REQUIRE(isRussian);
		}
	}
	WHEN("Word is not russian")
	{
		bool isRussian = false;
		std::string str = "Definitely not a russian string";
		THEN("isRussian is false")
		{
			SwitchIsRussian(str, isRussian);
			REQUIRE(!isRussian);
		}
	}
}

SCENARIO("Test toLowerCase")
{
	WHEN("String is on UpperCase")
	{
		std::string str = "HELLO WORLD";
		THEN("Finil string is on LowerCase")
		{
			str = TransormToLowerCase(str);
			REQUIRE(str == "hello world");
		}
	}
	WHEN("String is already at lowercase")
	{
		std::string str = "hello world";
		THEN("Finil string is at lowercase too")
		{
			str = TransormToLowerCase(str);
			REQUIRE(str == "hello world");
		}
	}
}

SCENARIO("Test FindTranslation")
{
	WHEN("Word is not in dictionary")
	{
		THEN("ostream is empty, findTranslation returned false")
		{
			bool isRussian = false;
			bool isWordAdded = false;
			Dictionaries dictionaries;
			std::string searchedString = "hello";
			std::ostringstream output;
			REQUIRE(!FindTranslation(isRussian, isWordAdded, dictionaries, searchedString, output));
			REQUIRE(output.str().empty());
		}
	}
	WHEN("Word is in dictionary and has 1 translation")
	{
		THEN("Ostream contains translation")
		{
			bool isRussian = false;
			bool isWordAdded = false;
			Dictionaries dictionaries;
			dictionaries.mainDict.emplace("hello", "привет");
			std::string searchedString = "hello";
			std::ostringstream output;
			REQUIRE(FindTranslation(isRussian, isWordAdded, dictionaries, searchedString, output));
			REQUIRE(output.str() == "привет\n");
		}
	}
	WHEN("Word is in dictionary and has 2 translation")
	{
		THEN("Ostream contains 2 translation")
		{
			bool isRussian = false;
			bool isWordAdded = false;
			Dictionaries dictionaries;
			dictionaries.mainDict.emplace("hello", "привет");
			dictionaries.mainDict.emplace("hello", "здравствуйте");
			std::string searchedString = "hello";
			std::ostringstream output;
			REQUIRE(FindTranslation(isRussian, isWordAdded, dictionaries, searchedString, output));
			REQUIRE(output.str() == "привет, здравствуйте\n");
		}
	}
}

SCENARIO("Test addTranslation")
{
	WHEN("Adding a translation to word")
	{
		THEN("Translation has been added and dictionary contains word and its translation")
		{
			bool isRussian = false;
			bool isWordAdded = false;
			Dictionaries dictionaries;
			std::string searchedString = "hello";
			std::string translationString = "привет";
			std::ostringstream output;
			AddTranslation(isWordAdded, isRussian, dictionaries, searchedString, translationString, output);
			REQUIRE(dictionaries.mainDict == std::multimap<std::string, std::string>{ { "hello", "привет" } });
			REQUIRE(dictionaries.sessionDict == std::multimap<std::string, std::string>{ { "hello", "привет" } });
			REQUIRE(output.str() == "—лово УhelloФ добавлено с переводом УприветФ.\n");
		}
	}
}