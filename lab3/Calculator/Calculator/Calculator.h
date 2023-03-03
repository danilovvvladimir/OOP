#pragma once
#include <map>
#include <optional>
#include <string>
#include <regex>

enum class Operation
{
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION
};

using Identifier = std::string;
using Value = double;

struct Expression
{
	Identifier firstOperand;
	Identifier secondOperand;
	Operation operation;
};

using Variables = std::map<Identifier, Value>;
using Functions = std::map<Identifier, Expression>;

class Calculator
{
public:
	Calculator();
	// isCorrect, isExist
	bool DefineVariable(Identifier& identifier);

	bool AssignVariable(Identifier& identifier, Value value);
	bool AssignFunction(Identifier& identifier, Value value);

	// isExist
	bool AssignVariable(Identifier& identifier1, Identifier& identifier2);
	bool AssignFunction(Identifier& identifier1, Identifier& identifier2);


	// precision 2
	//<- range for m_functions/m_variables
	Variables GetAllVariables(std::ostream& output) const;
	Functions GetAllFunctions(std::ostream& output) const; 

	// < -while& find
	std::optional<Value> GetVariableValue(Identifier& identifier) const;
	std::optional<Value> GetFunctionValue(Identifier& identifier) const;

	bool IsIdentifierCorrect(Identifier& identifier) const; // <- rules with RegExp ([a-zA-Z_][a-zA-z0-9_]*)
	bool IsIdentifierExist(Identifier& identifier) const; // <- not occupied (while&find for m_function&m_variables)
private:
	Functions m_functions;
	Variables m_variables;


	
	Value GetExpressionValue(Expression& expression) const; //<- operands & switch for Operations
};
