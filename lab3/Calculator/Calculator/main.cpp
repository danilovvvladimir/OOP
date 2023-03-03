#include "Calculator.h"
#include <iostream>
int main()
{
	Calculator calculator;
	Identifier id = "x";
	calculator.DefineVariable(id);
	std::cout << calculator.GetVariableValue(id).value() << std::endl;
	std::cout << NAN << std::endl;
	return 0;
}