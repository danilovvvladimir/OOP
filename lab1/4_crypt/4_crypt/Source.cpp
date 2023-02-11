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
				maskedByte <<= ENCRYPT_OFFSETS[i] - i;
			}
			else
			{
				maskedByte >>= i - ENCRYPT_OFFSETS[i];
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


int main()
{
	char ch = 5;
	ch = swapBits(ch, "crypt");
	ch = swapBits(ch, "encrypt");
	std::cout << int(ch) << std::endl;

	return 0;
}