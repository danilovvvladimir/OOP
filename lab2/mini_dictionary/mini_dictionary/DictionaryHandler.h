#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>

using Dictionary = std::multimap<std::string, std::string>;

struct Dictionaries
{
	Dictionary enToRuDict;
	Dictionary ruToEnDict;
	Dictionary currentDict;
	Dictionary sessionDict;
};

const int RUSSIAN_CHARS_UNICODE_START = -65;
const int RUSSIAN_BIG_CHARS_UNICODE_END = -65;
const int RUSSIAN_BIG_TO_SMALL_CHARS_CODE = 32;
const int RUSSIAN_CHARS_UNICODE_END = -1;

std::string TransormToLowerCase(bool const isRussian, std::string& searchedString);
std::string Trim(const std::string& source);
void InitDictionary(std::istream& inputFile, Dictionaries& dictionaries);
void SaveDictionary(std::ostream& outputFile, Dictionary& sessionDict, bool& isFileMissing);
void SwitchCurrentDict(std::string const& searchedString, bool& isRussian, Dictionaries& dictionaries);
void AddTranslation(bool& isWordAdded, bool& isRussian, Dictionaries& dictionaries, std::string& searchedString, std::string& translationString);
void FindTranslation(bool& isRussian, bool& isWordAdded, Dictionaries& dictionaries, std::string& searchedString);
void HandleSession(bool& isWordAdded, Dictionaries& dictionaries);
int HandleDictionary(std::string inputFilePath);