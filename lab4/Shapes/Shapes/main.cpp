#include "ShapesController.h"
#include <SFML/Graphics.hpp>
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
	shapesController.DrawShaped(800, 600, "Please work");
	shapesController.PrintMaxAreaShape();
	shapesController.PrintMinPerimeterShape();
	return 0;
}