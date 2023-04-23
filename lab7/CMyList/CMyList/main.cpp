#include "CMyList.hpp"
#include <iostream>
int main()
{
	CMyList<int> lst;
	int firstN = 100;
	int secondN = 200;
	int thirdN = 300;

	lst.Insert(lst.begin(), firstN);
	lst.PushBack(secondN);
	lst.PushBack(thirdN);


	for (auto& element : lst)
	{
		std::cout << element << std::endl;
	}
	return 0;
}