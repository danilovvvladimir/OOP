#include "Calculator.h"

// Start with AssingVar(id1,id2) tests for it have been done -> 99
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

bool Calculator::AssignFunction(Identifier& identifier1, Identifier& identifier2)
{
	return false;
}

Variables Calculator::GetAllVariables(std::ostream& output) const
{
	return Variables();
}

Functions Calculator::GetAllFunctions(std::ostream& output) const
{
	return Functions();
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

std::optional<Value> Calculator::GetVariableValue(Identifier& identifier) const
{
	if (!IsIdentifierCorrect(identifier) || !IsIdentifierExist(identifier))
	{
		return std::nullopt;
	}
	auto variable = m_variables.find(identifier);
	return variable->second;
}

// ¬ычисленное значение функции
// т.е, € нахожу expression и его прогон€ю
std::optional<Value> Calculator::GetFunctionValue(Identifier& identifier) const
{
	return std::optional<Value>();
}

Value Calculator::GetExpressionValue(Expression& expression) const
{
	return Value();
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

//start
bool Calculator::AssignVariable(Identifier& identifier1, Identifier& identifier2)
{
	return false;
}

bool Calculator::AssignFunction(Identifier& identifier, Value value)
{
	return false;
}
