#include "../MyString/CMyString.h"

#include <iostream>
#include <sstream>
#include <fstream>
int main()
{
	CMyString str1 = "Hello";
	 str1 += " world";
	std::cout << str1 << std::endl;

	return 0;
}