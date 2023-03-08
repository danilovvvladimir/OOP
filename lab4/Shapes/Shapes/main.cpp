#include "ShapesController.h"
#include <iostream>

int main()
{
	//make_shared -> static method in point
	// parse args сделать для каждого create shape
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