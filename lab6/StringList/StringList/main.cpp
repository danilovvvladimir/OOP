#include "CStringList.h"
#include <iostream>
#include <list>

#include <string>
#include <vector>

int main()
{
	std::string str1("111");

	//std::list<std::string> lst;
	//lst.insert(lst.begin(), str1);
	//for (auto el : lst)
	//{
	//	std::cout << el << std::endl;
	//}

	CStringList lst;
	lst.PushBack("1");
	lst.PushBack("2");
	lst.PushBack("3");
	std::cout << lst.GetSize() << std::endl;

	std::for_each(lst.begin(), lst.end(), [](std::string& el) {
		std::cout << el << std::endl;
	});



	return 0;
}