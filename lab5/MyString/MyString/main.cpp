#include "../MyString/CMyString.h"

#include <iostream>
#include <sstream>
#include <fstream>
int main()
{
	CMyString str = "Hello world";
	CMyString newStr(std::move(str));
	std::cout << str.GetLength() << std::endl;
	std::cout << newStr.GetLength() << std::endl;

	return 0;
}