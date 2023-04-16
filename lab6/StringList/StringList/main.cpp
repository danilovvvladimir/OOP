#include "CStringList.h"
#include <iostream>
#include <vector>
#include <list>
int main()
{

	CStringList lst1 = CStringList();
	lst1.PushBack("Hello");

	lst1.~CStringList();


	return 0;
}