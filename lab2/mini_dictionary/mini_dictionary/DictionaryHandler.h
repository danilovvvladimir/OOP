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
	Dictionary mainDict;
	Dictionary sessionDict;
};

const int RUSSIAN_CHARS_UNICODE_START = -65;
const int RUSSIAN_CHARS_UNICODE_END = -1;

std::string TransormToLowerCase(std::string& searchedString);
	std::string Trim(const std::string& source);
int HandleDictionary(std::string inputFilePath, std::istream& input, std::ostream& output);
void InitDictionary(std::istream& inputFile, Dictionary& mainDict);
void HandleSession(bool& isWordAdded, Dictionaries& dictionaries, std::istream& input, std::ostream& output);
void SwitchIsRussian(std::string const& searchedString, bool& isRussian);
bool FindTranslation(bool& isRussian, bool& isWordAdded, Dictionaries& dictionaries, std::string& searchedString, std::ostream& output);
void HandleAddingTranslation(std::string& searchedString, bool& isRussian, bool& isWordAdded, Dictionaries& dictionaries, std::istream& input, std::ostream& output);
void AddTranslation(bool& isWordAdded, bool& isRussian, Dictionaries& dictionaries, std::string& searchedString, std::string& translationString, std::ostream& output);
void SaveDictionary(std::ostream& outputFile, Dictionary& sessionDict, bool& isFileMissing, std::istream& input, std::ostream& output);
std::string GetNewDictionaryPath(std::ostream& output);
bool HandleSavingDictionary(bool& isFileMissing, Dictionaries& dictionaries, std::ostream& inputFile, std::istream& input, std::ostream& output);
