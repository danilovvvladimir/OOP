#include <fstream>
#include <iostream>
#include <optional>
#include <string>

const int BYTE_LENGTH = 8;
const std::string STRING_MODE_CRYPT = "crypt";
const std::string STRING_MODE_DECRYPT = "decrypt";

enum class CryptMode
{
	Crypt,
	Decrypt,
};

struct Args
{
	CryptMode cryptMode;
	std::string inputFileName;
	std::string outputFileName;
	int key;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage crypt.exe crypt <input file> <output file> <key> \n"
				  << "or\n Usage crypt.exe decrypt <input file> <output file> <key>\n";

		return std::nullopt;
	}

	Args args;
	if (argv[1] == STRING_MODE_CRYPT)
	{
		args.cryptMode = CryptMode::Crypt;
	}
	else if (argv[1] == STRING_MODE_DECRYPT)
	{
		args.cryptMode = CryptMode::Decrypt;
	}
	else
	{
		std::cout << "Invalid cryptMode: try \"crypt\" or \"decrypt\"" << std::endl;
		return std::nullopt;
	}

	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.key = std::stoi(argv[4]);

	if (args.key < 0 || args.key > 255)
	{
		std::cout << "Invalid key: key should be in interval 0-255" << std::endl;
		return std::nullopt;
	}

	return args;
}

char SwapBits(char startedByte, const CryptMode & mode)
{
	const int ENCRYPT_OFFSETS[BYTE_LENGTH] = { 2, 3, 4, 6, 7, 0, 1, 5 };
	const int DECRYPT_OFFSETS[BYTE_LENGTH] = { 5, 6, 0, 1, 2, 7, 3, 4 };

	char finalByte = 0;

	for (int i = 0; i < BYTE_LENGTH; i++)
	{
		char byteMask = static_cast<char>(pow(2, i));
		unsigned char maskedByte = startedByte & byteMask;

		if (mode == CryptMode::Crypt)
		{
			if ((ENCRYPT_OFFSETS[i] - i) >= 0)
			{
				maskedByte = maskedByte << (ENCRYPT_OFFSETS[i] - i);
			}
			else
			{
				maskedByte = maskedByte >> (i - ENCRYPT_OFFSETS[i]);
			}
		}
		else
		{
			if ((DECRYPT_OFFSETS[i] - i) >= 0)
			{
				maskedByte = maskedByte << (DECRYPT_OFFSETS[i] - i);
			}
			else
			{
				maskedByte = maskedByte >> (i - DECRYPT_OFFSETS[i]);
			}
		}
		finalByte = finalByte | maskedByte;
	}
	return finalByte;
}

char EncryptByte(char currentByte, int key)
{
	currentByte = currentByte ^ key;
	return SwapBits(currentByte, CryptMode::Crypt);
}
char DecryptByte(char currentByte, int key)
{
	currentByte = SwapBits(currentByte, CryptMode::Decrypt);
	return currentByte ^ key;
}

void EncryptFile(std::istream& inputFile, std::ostream& outputFile, int key)
{
	while (!inputFile.eof())
	{
		char currentByte;
		inputFile.read(&currentByte, 1);
		if (inputFile.eof())
		{
			return;
		}
		currentByte = EncryptByte(currentByte, key);

		outputFile << currentByte;
	}
}
void DecryptFile(std::istream& inputFile, std::ostream& outputFile, int key)
{
	while (!inputFile.eof())
	{
		char currentByte;
		inputFile.read(&currentByte, 1);
		if (inputFile.eof())
		{
			return;
		}
		currentByte = DecryptByte(currentByte, key);

		outputFile << currentByte;
	}
}

int HandleCryptation(const CryptMode& cryptMode, const std::string& inputFilePath, const std::string& outputFilePath, int key)
{

	std::ifstream inputFile;
	std::ofstream outputFile;

	inputFile.open(inputFilePath, std::ios_base::binary);
	if (!inputFile.is_open())
	{
		std::cout << "Couldn't open INPUT file" << std::endl;
		return 1;
	}
	outputFile.open(outputFilePath, std::ios_base::binary);
	if (!outputFile.is_open())
	{
		std::cout << "Couldn't open OUTPUT file" << std::endl;
		return 1;
	}

	if (cryptMode == CryptMode::Crypt)
	{
		EncryptFile(inputFile, outputFile, key);
	}
	else
	{
		DecryptFile(inputFile, outputFile, key);
	}

	return 0;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	int statusCode = HandleCryptation(args->cryptMode, args->inputFileName, args->outputFileName, args->key);
	if (statusCode != 0)
	{
		return 1;
	}

	return 0;
}
