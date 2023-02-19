#include "DictionaryHandler.h"

int main(int argc, char* argv[])
{
	system("chcp 1251 > nul");
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	int statusCode = HandleDictionary(args->inputFilePath);
	if (statusCode != 0)
	{
		return 1;
	}

	return 0;
}
