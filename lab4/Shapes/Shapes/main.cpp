#include "ShapesController.h"
#include <iostream>

int main()
{
	//make_shared -> static method in point
	// maxarea, minperimeter
	ShapesController shapesController(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!shapesController.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;
}