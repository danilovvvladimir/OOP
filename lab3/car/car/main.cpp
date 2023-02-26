#include "CarRemoteController.h"

int main()
{
	Car car;
	CarRemoteController carRemoteController(car, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!carRemoteController.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return 0;
}