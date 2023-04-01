#include "CHttpUrl.h"
#include <iostream>

int main()
{
	CHttpUrl c("vk.com", "/fas", Protocol::HTTP);
	std::cout << c.GetURL()<<std::endl;
	return 0;
}