#include <iostream>
#include <string>
#include <fstream>



//==2==Чтение текста из IN файла построчно. (открыты как IN, так и OUT файлы).
//==1== Замена подстроки в строке
//	- Нахождение количества вхождений в строку подстроки.
//	- Циклом с количеством итераций, найденных выше:
//		- Ищем эту подстроку(первый индекс) (find - даёт индекс);
//		- До этого индекса строку засовываю в stringFirstHalf, после этого индекса+длины подстроки начальной до конца в stringSecondHalf;
//		- Склеиваю stringFirstHalf + новая подстрока + stringSecondHalf;
//		//и так в цикле, пока не будут изменены все вхождения !!!!!!!!!!!!!!подумать про многократное вхождение строки (контрится указанием индекса с которого будет идти цикл)
//==3==Вывод этой строки в OUT файл.
//
// Разбиение на функции.
// Обработка ошибок.
//
//
// .find(substring, INDEXofstart)!!!!!!!!!!!!!!!!!!!!!

int count_of_substrings(std::string src, std::string sub) {
	int start = 0;
	int count = 0;
	int pos = 0;
	for (;;) {
		pos = src.find(sub.c_str(), start);
		if (pos != -1) {
			start = pos + sub.size();
			count++;
		}
		else {
			break;
		}
	}
	return count;
}

std::string replaceSubstring(std::string mainStr, std::string substrFirst, std::string substrSecond)
{
	std::string strResult = mainStr;
	int lengthSubstringNormal = substrFirst.size();
	int lengthSubstringNeeded = substrSecond.size();
	int indexOfStart = 0;
	int countSubstring = count_of_substrings(strResult, substrFirst);

	if (countSubstring > 0)
	{
		for (int k = 0; k < countSubstring; k++)
		{
			int lengthStrIN = strResult.size();
			std::string stringFirstHalf = "";
			std::string stringSecondHalf = "";
			int temp = strResult.find(substrFirst, indexOfStart);
			//std::cout << "indexOfStart: " << indexOfStart << std::endl;
			//std::cout << "indexOfSubstringStart: " << temp << std::endl;
			indexOfStart = temp + lengthSubstringNeeded;


			for (int i = 0; i < lengthStrIN; i++)
			{

				if (i < temp)
				{
					stringFirstHalf += strResult[i];
				}
				else
				{
					if (i >= temp + lengthSubstringNormal)
					{
						stringSecondHalf += strResult[i];
					}
				}
			}
			strResult = stringFirstHalf + substrSecond + stringSecondHalf;
		}
	}
	return strResult;
}

int main()
{
	std::string substringNormal = "1231234";
	std::string substringNeeded = "NOT NEEDLE";


	std::ifstream fIN;
	std::ofstream fOUT;

	std::string fINpath = "in.txt";
	std::string fOUTpath = "out.txt";

	fIN.open(fINpath);
	if (fIN.is_open())
	{
		fOUT.open(fOUTpath);
		if (fOUT.is_open())
		{
			while (!fIN.eof())
			{
				std::string line = "";
				std::getline(fIN, line);
				line = replaceSubstring(line, substringNormal, substringNeeded);
				fOUT << line << std::endl;

			}
			fOUT.close();
			fIN.close();
		}
		else
		{
			std::cout << "OUT File couldn't been opened" << std::endl;
			return 1;
		}
	}
	else
	{
		std::cout << "IN File couldn't been opened" << std::endl;
		return 1;
	}


	return 0;
}