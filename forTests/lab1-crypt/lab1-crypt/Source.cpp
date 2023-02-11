#include <iostream>
#include <fstream>
#include <string>


int main()
{
	system("chcp 1251 > nul");


	std::cout << "Enter the mode: 1 - toBinary(write message), 2 - fromBinary(read message): " << std::endl;
	int mode;
	std::cin >> mode;

	if (mode == 1)
	{
		std::string outPath;
		std::cout << "Enter the <output.bin> file: ";
		std::cin >> outPath;

		std::cout << "Enter the message: ";
		char x[1024];
		std::string str;

		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::getline(std::cin, str);
		strcpy_s(x, str.c_str());

		std::ofstream fout;
		fout.open(outPath, std::ios_base::binary);
		fout.write((char*)&x, sizeof(x));
		fout.close();
	}
	else
	{
		if (mode == 2)
		{
			std::string inPath;
			std::cout << "Enter the <input.bin> file: ";
			std::cin >> inPath;

			char answer[1024];
			std::ifstream fin;
			fin.open(inPath, std::ios_base::binary);
			fin.read((char*)&answer, sizeof(answer));
			fin.close();

			std::cout << answer << std::endl;
		}
		else
		{
			std::cout << "Enter the mode: 1 - toBinary, 2 - fromBinary!" << std::endl;
		}
	}



	;

	return 0;
}