#include "DictionaryHandler.h"

struct Args
{
	std::string inputFilePath;
};

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

int main(int argc, char* argv[])
{
	system("chcp 1251 > nul");
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	int statusCode = HandleDictionary(args->inputFilePath, std::cin, std::cout);
	if (statusCode != 0)
	{
		return 1;
	}

	return 0;
}
