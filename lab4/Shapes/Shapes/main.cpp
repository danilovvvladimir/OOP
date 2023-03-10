#include "ShapesController.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream inputFile;
	inputFile.open("input.txt");
	std::istream& inputStream = inputFile;

	//std::istream& inputStream = std::cin;

	ShapesController shapesController(inputStream, std::cout);
	while (!inputStream.eof() && !inputStream.fail())
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