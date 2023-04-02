#include "CHttpUrl.h"
#include <iostream>

int main()
{

	try
	{
		CHttpUrl c("http://vk.com/fruityflunt/fdag.jpg");

		std::cout << static_cast<int>(c.GetProtocol()) << std::endl;
		std::cout << c.GetDomain() << std::endl;
		std::cout << c.GetPort() << std::endl;
		std::cout << c.GetDocument() << std::endl;
		std::cout << c.GetURL() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}