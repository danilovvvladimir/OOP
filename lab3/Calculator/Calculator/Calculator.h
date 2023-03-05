#pragma once
#include <map>
#include <optional>
#include <string>
#include <regex>
#include <limits>

enum class Operation
{
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	NONE
};

using Identifier = std::string;
using Value = double;

struct Expression
{
	Identifier firstOperand;
	Operation operation;
	Identifier secondOperand;
};

using Variables = std::map<Identifier, Value>;
using Functions = std::map<Identifier, Expression>;

const Value NAN_VALUE = std::numeric_limits<Value>::quiet_NaN();


class Calculator
{
public:
	Calculator();
	bool DefineVariable(Identifier& identifier);

	bool AssignVariable(Identifier& identifier, Value value);
	bool AssignVariable(Identifier& identifier1, Identifier& identifier2);
	bool AssignFunction(Identifier& identifier, Expression expression);
	bool AssignFunction(Identifier& identifier1, Identifier& identifier2);

	Variables GetAllVariables() const;
	Functions GetAllFunctions() const; 

	std::optional<Value> GetVariableValue(Identifier& identifier) const;
	std::optional<Value> GetFunctionValue(Identifier& identifier) const;

	// mb private
	std::optional<Expression> GetFunctionExpression(Identifier& Expression) const;
	Value GetExpressionValue(Expression& expression) const;
	bool IsIdentifierCorrect(Identifier& identifier) const;
	bool IsIdentifierExist(Identifier& identifier) const;
private:
	Functions m_functions;
	Variables m_variables;
};
