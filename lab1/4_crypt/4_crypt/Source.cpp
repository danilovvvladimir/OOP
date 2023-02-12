#include <fstream>
#include <iostream>
#include <string>

char swapBits(char startedByte, std::string mode)
{
	const int ENCRYPT_OFFSETS[8] = { 2, 3, 4, 6, 7, 0, 1, 5 };
	const int DECRYPT_OFFSETS[8] = { 5, 6, 0, 1, 2, 7, 3, 4 };
	const int BYTE_LENGTH = 8;
	char finalByte = 0;

	for (int i = 0; i < BYTE_LENGTH; i++)
	{
		char byteMask = static_cast<char>(pow(2, i));
		unsigned char maskedByte = startedByte & byteMask;

		if (mode == "crypt")
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
// encrypt decrypt BYTE

char encryptByte(char currentByte, int key)
{
	currentByte = currentByte ^ key;
	return swapBits(currentByte, "crypt");
}
char decryptByte(char currentByte, int key)
{
	currentByte = swapBits(currentByte, "decrypt");
	return currentByte ^ key;
}

void encryptFile(std::istream& inputFile, std::ostream& outputFile, int key)
{
	while (!inputFile.eof())
	{
		char currentByte;
		inputFile.read(&currentByte, 1);
		if (inputFile.eof())
		{
			return;
		}
		currentByte = encryptByte(currentByte, key);

		outputFile << currentByte;
	}
}
void decryptFile(std::istream& inputFile, std::ostream& outputFile, int key)
{
	while (!inputFile.eof())
	{
		char currentByte;
		inputFile.read(&currentByte, 1);
		if (inputFile.eof())
		{
			return;
		}
		currentByte = decryptByte(currentByte, key);

		outputFile << currentByte;
	}
}

int HandleCryptation(std::string mode, std::string inputFilePath, std::string outputFilePath, std::string keyString)
{
	std::string cryptMode = mode;
	if (cryptMode != "crypt" && cryptMode != "decrypt")
	{
		std::cout << "Invalid cryptMode: try \"crypt\" or \"decrypt\"" << std::endl;
		return 1;
	}
	int key = std::stoi(keyString);
	if (key < 0 || key > 255)
	{
		std::cout << "Invalid key: key should be in interval 0-255" << std::endl;
		return 1;
	}

	std::ifstream inputFile;
	std::ofstream outputFile;

	inputFile.open(inputFilePath, std::ios_base::binary);
	if (inputFile.is_open())
	{
		outputFile.open(outputFilePath, std::ios_base::binary);
		if (outputFile.is_open())
		{
			if (cryptMode == "crypt")
			{
				encryptFile(inputFile, outputFile, key);
			}
			else
			{
				decryptFile(inputFile, outputFile, key);
			}
			//outputFile.close();
			//inputFile.close();
		}
		else
		{
			inputFile.close();
			std::cout << "Couldn't open OUTPUT file" << std::endl;
			return 1;
		}
	}
	else
	{
		std::cout << "Couldn't open INPUT file" << std::endl;
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{

	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage crypt.exe crypt <input file> <output file> <key> \n"
				  << "or\n Usage crypt.exe decrypt <input file> <output file> <key>\n";

		return 1;
	}

	int statusCode = HandleCryptation(argv[1], argv[2], argv[3], argv[4]);
	if (statusCode != 0)
	{
		return 1;
	}

	return 0;
}
