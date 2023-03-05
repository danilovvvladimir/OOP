#include "Calculator.h"
#include <iostream>
int main()
{
	Calculator calculator;
	Identifier var1 = "x";
	Identifier var2 = "y";

	Value var1Value = 3;
	Value var2Value = 4;
	calculator.AssignVariable(var1, var1Value);
	calculator.AssignVariable(var2, var2Value);

	Identifier function1 = "XplusY";
	Expression expression1 = { var1, Operation::ADDITION, var2 };
	calculator.AssignFunction(function1, expression1);
	std::cout << (calculator.GetFunctionValue(function1).value() == var1Value + var2Value) << std::endl; // 1

	Value var1ValueNew = 10;
	calculator.AssignVariable(var1, var1ValueNew);
	std::cout << (calculator.GetFunctionValue(function1).value() == var1ValueNew + var2Value) << std::endl; // 1

	Identifier var3 = "z";
	Value var3Value = 3.5;
	calculator.AssignVariable(var3, var1Value);

	Identifier function2 = "XplusYdivZ";
	Expression expression2 = { function1, Operation::DIVISION, var3 };
	calculator.AssignFunction(function2, expression2);

	std::cout << calculator.GetFunctionValue(function2).value() << std::endl;
	/*;
	REQUIRE();
	
	REQUIRE( == (var1ValueNew + var2Value) / var3Value);*/
	return 0;
}