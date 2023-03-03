#pragma once
#include <map>
#include <string>
#include <optional>

class Calculator
{
public:
	enum class Operation
	{
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION,
		DIVISION
	};
	using Identifier = std::string;
	using Value = double;
	using Expression = struct
	{
		Identifier firstOperand;
		Identifier secondOperand;
		Operation operation;
	};
	using Variables = std::map<Identifier, Value>;
	using Functions = std::map<Identifier, Expression>;

	// bool DefineVar, bool DefineFn,									<- IsIdentifierCorrect
																		   
	// bool AssingVar(value), bool AssingVar(var)						<- IsIdentifierExist
	// bool AssingFn(expression), bool AssingFn(fn)					<- IsIdentifierExist

	// printVars() const, printFnctns() const							<- range for m_functions/m_variables

	// print(var) const, print(fn) const								<- while & find
private:
	Functions m_functions;
	Variables m_variables;
	// bool IsIdentifierCorrect(Identifier) const						<- rules with RegExp ([a-zA-Z_][a-zA-z0-9_]*)
	// bool IsIdentifierExist(Identifier) const							<- not occupied (while&find for m_function&m_variables)

	// std::optional<Value> GetVariableValue(Identifier) const			<- while & find m_variables
	// std::optional<Value> GetFunctionValue(Identifier) const			<- while & find m_functions

	// Value GetExpressionValue(Expression) const						<- operands & switch for Operations
	
};
