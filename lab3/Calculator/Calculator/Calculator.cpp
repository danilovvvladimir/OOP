#include "Calculator.h"

Calculator::Calculator()
	: m_functions({})
	, m_variables({})
{
}

bool Calculator::DefineVariable(Identifier& identifier)
{
	if (!IsIdentifierCorrect(identifier) || IsIdentifierExist(identifier))
	{
		return false;
	}

	m_variables.emplace(identifier, NAN_VALUE);
	return true;
}

bool Calculator::AssignVariable(Identifier& identifier, Value value)
{
	if (IsIdentifierExist(identifier))
	{
		m_variables[identifier] = value;
		return true;
	}

	if (IsIdentifierCorrect(identifier))
	{
		DefineVariable(identifier);
		m_variables[identifier] = value;
		return true;
	}

	return false;
}

bool Calculator::AssignVariable(Identifier& identifier1, Identifier& identifier2)
{
	if (!IsIdentifierExist(identifier2))
	{
		return false;
	}

	if (!IsIdentifierExist(identifier1))
	{
		if (!IsIdentifierCorrect(identifier1))
		{
			return false;
		}
		DefineVariable(identifier1);
	}

	if (IsFunctionExist(identifier2))
	{
		auto it = m_functions.find(identifier2);
		m_variables[identifier1] = GetExpressionValue(it->second);
		return true;
	}

	auto it = m_variables.find(identifier2);
	m_variables[identifier1] = it->second;
	return true;
}

std::optional<Value> Calculator::GetVariableValue(Identifier& identifier) const
{
	if (!IsIdentifierExist(identifier))
	{
		return std::nullopt;
	}
	auto variable = m_variables.find(identifier);
	return variable->second;
}

Variables Calculator::GetAllVariables() const
{
	return m_variables;
}

bool Calculator::IsIdentifierCorrect(Identifier& identifier) const
{
	std::smatch result;
	std::regex regex("([a-zA-Z_][a-zA-Z0-9_]*)");
	if (!regex_match(identifier, result, regex))
	{
		return false;
	}
	return true;
}

bool Calculator::IsIdentifierExist(Identifier& identifier) const
{
	if (!IsFunctionExist(identifier) && !IsVariableExist(identifier))
	{
		return false;
	}
	return true;
}

bool Calculator::IsFunctionExist(Identifier& identifier) const
{
	if (m_functions.find(identifier) == m_functions.end())
	{
		return false;
	}
	return true;
}

bool Calculator::IsVariableExist(Identifier& identifier) const
{
	if (m_variables.find(identifier) == m_variables.end())
	{
		return false;
	}
	return true;
}

bool Calculator::AssignFunction(Identifier& identifier, Expression expression)
{
	if (!IsIdentifierCorrect(identifier))
	{
		return false;
	}

	if (IsIdentifierExist(identifier))
	{
		return false;
	}

	if (!IsIdentifierExist(expression.firstOperand) || !IsIdentifierExist(expression.secondOperand))
	{
		return false;
	}

	m_functions.emplace(identifier, expression);
	return true;
}

bool Calculator::AssignFunction(Identifier& identifier1, Identifier& identifier2)
{
	if (IsIdentifierExist(identifier1) || !IsIdentifierExist(identifier2))
	{
		return false;
	}

	if (!IsIdentifierCorrect(identifier1))
	{
		return false;
	}

	m_functions.emplace(identifier1, Expression{ identifier2, Operation::NONE, identifier2 });
	return true;
}

std::optional<Expression> Calculator::GetFunctionExpression(Identifier& identifier) const
{
	if (!IsIdentifierExist(identifier))
	{
		return std::nullopt;
	}
	auto expression = m_functions.find(identifier);
	return expression->second;
}

Value Calculator::GetExpressionValue(Expression& expression) const
{
	Value firstOperandValue;
	Value secondOperandValue;

	if (m_variables.find(expression.firstOperand) != m_variables.end())
	{
		firstOperandValue = GetVariableValue(expression.firstOperand).value();
	}
	else
	{
		Expression tempExpression = m_functions.find(expression.firstOperand)->second;
		firstOperandValue = GetExpressionValue(tempExpression);
	}

	if (m_variables.find(expression.secondOperand) != m_variables.end())
	{
		secondOperandValue = GetVariableValue(expression.secondOperand).value();
	}
	else
	{
		Expression tempExpression = m_functions.find(expression.secondOperand)->second;
		secondOperandValue = GetExpressionValue(tempExpression);
	}

	switch (expression.operation)
	{
	case Operation::ADDITION:
		return firstOperandValue + secondOperandValue;
	case Operation::SUBTRACTION:
		return firstOperandValue - secondOperandValue;
	case Operation::MULTIPLICATION:
		return firstOperandValue * secondOperandValue;
	case Operation::DIVISION:
		return firstOperandValue / secondOperandValue;
	default:
		return firstOperandValue;
	}
}

std::optional<Value> Calculator::GetFunctionValue(Identifier& identifier) const
{
	if (!IsIdentifierExist(identifier))
	{
		return std::nullopt;
	}
	Expression functionExpression = GetFunctionExpression(identifier).value();
	return GetExpressionValue(functionExpression);
}

Functions Calculator::GetAllFunctions() const
{
	return m_functions;
}
