#include "ShapesController.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

int main()
{
	//fix area with abs

	std::ifstream inputFile;
	inputFile.open("input.txt");
	ShapesController shapesController(inputFile, std::cout);

	//ShapesController shapesController(std::cin, std::cout);
	//while (!std::cin.eof() && !std::cin.fail())
	while (!inputFile.eof() && !inputFile.fail())
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