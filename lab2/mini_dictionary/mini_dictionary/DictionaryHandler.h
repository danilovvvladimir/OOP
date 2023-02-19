#pragma once
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

std::string TransormToLowerCase(bool const isRussian, std::string& searchedString);
std::string Trim(const std::string& source);
void InitDictionary(std::istream& inputFile, Dictionary& enToRuDict, Dictionary& ruToEnDict);
void SaveDictionary(std::ostream& outputFile, Dictionary& sessionDict, bool& isFileMissing);
void AddTranslation(bool& isWordAdded, bool& isRussian, Dictionary& ruToEnDict, Dictionary& enToRuDict, Dictionary& sessionDict, std::string& searchedString, std::string& translationString);
void FindTranslation(bool& isRussian, bool& isWordAdded, Dictionary& enToRuDict, Dictionary& ruToEnDict, Dictionary& mainDict, Dictionary& sessionDict, std::string& searchedString);
void HandleSession(bool& isWordAdded, Dictionary& enToRuDict, Dictionary& ruToEnDict, Dictionary& mainDict, Dictionary& sessionDict);
std::optional<Args> ParseArgs(int argc, char* argv[]);
int HandleDictionary(std::string inputFilePath);