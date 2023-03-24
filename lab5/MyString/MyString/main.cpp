#include "../MyString/CMyString.h"

#include <iostream>

int main()
{
	CMyString str("abcd1234");
	std::cout << str << std::endl;

	CMyString str2 = str.SubString(4, 3);
	std::cout << str2 << std::endl;
	return 0;
}