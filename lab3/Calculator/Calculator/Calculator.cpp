#include "Calculator.h"

// AssingFunction tests nado!

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

	m_variables.emplace(identifier, NAN);
	return true;
}

bool Calculator::AssignVariable(Identifier& identifier, Value value)
{
	// если не существует, то провер€ю на корректность и создаю
	// если существует то, значение прибавл€ю
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
	// если не существует id2, to false

	// если не существует id1, то чекаю на корректность, если incorrect то false
	// ищу в мэпе id2 и создаю новую пару id1 + id2->value
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

	auto it = m_variables.find(identifier2);
	m_variables[identifier1] = it->second;
	return true;
}

std::optional<Value> Calculator::GetVariableValue(Identifier& identifier) const
{
	if (!IsIdentifierCorrect(identifier) || !IsIdentifierExist(identifier))
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
	if (m_functions.find(identifier) == m_functions.end() && m_variables.find(identifier) == m_variables.end())
	{
		return false; // doesn't exist
	}
	return true; // exist
}

//---
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

	m_functions.emplace(identifier, expression);
	return false;
}
//---
bool Calculator::AssignFunction(Identifier& identifier1, Identifier& identifier2)
{
	return false;
}

//---
// ¬ычисленное значение функции
// т.е, € нахожу expression и его прогон€ю
std::optional<Expression> Calculator::GetFunctionExpression(Identifier& identifier) const
{
	return std::optional<Expression>();
}

//---
Value Calculator::GetExpressionValue(Expression& expression) const
{
	return Value();
}

Functions Calculator::GetAllFunctions() const
{
	return m_functions;
}
