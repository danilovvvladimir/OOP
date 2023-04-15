#include "CStringList.h"
#include <iostream>
#include <list>

#include <string>
#include <vector>

int main()
{

	CStringList lst;
	lst.PushBack("333");
	lst.PushBack("444");
	lst.PushBack("555");

	for (auto it = lst.cbegin(); it != lst.cend(); it++)
	{
		std::cout << *it << std::endl;
	}
	
	lst.~CStringList();

	return 0;
}