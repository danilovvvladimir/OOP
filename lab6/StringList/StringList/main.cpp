#include "CStringList.h"
#include <iostream>
#include <vector>
int main()
{
	CStringList lst;

	lst.PushBack("1");
	lst.PushBack("2");
	lst.PushBack("3");

	std::cout << lst.GetSize() << std::endl;

	CStringList lstCopy(lst);
	std::cout << lstCopy.GetSize() << std::endl;
	std::vector<int> v;
	v.erase(v.begin());
	
	return 0;
}