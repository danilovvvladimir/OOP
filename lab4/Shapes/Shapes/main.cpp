#include "ShapesController.h"
#include <iostream>

int main()
{
	ShapesController shapesController(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!shapesController.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	shapesController.PrintMaxAreaShape();
	shapesController.PrintMinPerimeterShape();
	return 0;
}