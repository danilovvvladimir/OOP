#include "CStringList.h"
#include <string>
#include <iostream>


int main()
{
	CStringList lst;
	lst.PushBack("sad");
	lst.PushFront("123");
	lst.PushFront("1233");
	//CStringList lst2(lst);
	std::cout << lst.GetSize() << std::endl;
	return 0;
}