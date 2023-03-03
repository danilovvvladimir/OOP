#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Calculator/Calculator.h"

SCENARIO("Testing isIdentifierCorrect")
{
	Calculator calculator;
	WHEN("Identifier is empty")
	{
		THEN("Identifier is not correct")
		{
			Identifier identifier = "";
			REQUIRE(!calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier is digit")
	{
		THEN("Identifier is not correct")
		{
			Identifier identifier = "1";
			REQUIRE(!calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier is letter")
	{
		THEN("Identifier is correct")
		{
			Identifier identifier = "a";
			REQUIRE(calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier starting with digit")
	{
		THEN("Identifier is not correct")
		{
			Identifier identifier = "1amount";
			REQUIRE(!calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier starting with letter")
	{
		THEN("Identifier is correct")
		{
			Identifier identifier = "amount1";
			REQUIRE(calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier starting with Capital letter")
	{
		THEN("Identifier is correct")
		{
			Identifier identifier = "Amount1";
			REQUIRE(calculator.IsIdentifierCorrect(identifier));
		}
	}
	WHEN("Identifier doesn't contain digit")
	{
		THEN("Identifier is correct")
		{
			Identifier identifier = "amount";
			REQUIRE(calculator.IsIdentifierCorrect(identifier));
		}
	}
}

// Тест при existed function with needed identifier
SCENARIO("Testing IsIdentifierExist")
{
	
	WHEN("Identifier doesn't exist")
	{
		Calculator calculator;
		THEN("Return FALSE = identifier is not occupied")
		{
			Identifier identifier = "amount";
			REQUIRE(!calculator.IsIdentifierExist(identifier));
		}
	}
	WHEN("Identifier exists")
	{
		Calculator calculator;
		Identifier identifier = "amount";
		calculator.DefineVariable(identifier);
		THEN("Return TRUE = identifier is occupied")
		{
			Identifier identifierCopy = "amount";
			REQUIRE(calculator.IsIdentifierExist(identifierCopy));
		}
	}
}

SCENARIO("Testing DefineVariable")
{
	WHEN("Identifier is not occupied and correctly written")
	{
		Calculator calculator;
		THEN("Identifier is defined")
		{
			Identifier identifier = "excellentIdentifierName";
			REQUIRE(calculator.DefineVariable(identifier));
		}
	}
	WHEN("Identifier is occupied and correctly written")
	{
		Calculator calculator;
		THEN("Identifier is not defined")
		{
			Identifier identifier1 = "excellentIdentifierName";
			REQUIRE(calculator.DefineVariable(identifier1));

			Identifier identifier2 = "excellentIdentifierName";
			REQUIRE(!calculator.DefineVariable(identifier2));
		}
	}
	WHEN("Identifier is not occupied but incorrectly written")
	{
		Calculator calculator;
		THEN("Identifier is not defined")
		{
			Identifier identifier1 = "1Terrible(Identifier=Name";
			REQUIRE(!calculator.DefineVariable(identifier1));
		}
	}
}

// Тест на значения после добавления assign
SCENARIO("Testing GetVariableValue")
{
	WHEN("Variable doesn't exist")
	{
		Calculator calculator;
		THEN("Return FALSE, value = std::nullopt")
		{
			Identifier identifier = "x";
			REQUIRE(!calculator.GetVariableValue(identifier));
			REQUIRE(calculator.GetVariableValue(identifier) == std::nullopt);
		}
	}
	WHEN("Variable exist, but its value is NAN")
	{
		Calculator calculator;
		THEN("Returned Value is NAN")
		{
			Identifier identifier = "x";
			REQUIRE(calculator.DefineVariable(identifier));

			REQUIRE(isnan(calculator.GetVariableValue(identifier).value()));
		}
	}
}

SCENARIO("Testing AssignVariable with value")
{
	WHEN("Variable doesn't exist")
	{
		Calculator calculator;
		THEN("New variable has been created and assinged with the value")
		{
			Identifier identifier = "x";
			Value value = 1.245;
			REQUIRE(!calculator.IsIdentifierExist(identifier));

			REQUIRE(calculator.AssignVariable(identifier, value));
			REQUIRE(calculator.IsIdentifierExist(identifier));

			REQUIRE(calculator.GetVariableValue(identifier).value() == value);
		}
	}
	WHEN("Variable exist")
	{
		Calculator calculator;
		THEN("Variable assinged with the value")
		{
			Identifier identifier = "x";
			Value value = 1.245;
			REQUIRE(calculator.DefineVariable(identifier));
			REQUIRE(calculator.IsIdentifierExist(identifier));

			REQUIRE(calculator.AssignVariable(identifier, value));
			REQUIRE(calculator.IsIdentifierExist(identifier));
			REQUIRE(calculator.GetVariableValue(identifier).value() == value);

		}
	}
}

SCENARIO("Testing AssignVariable with another variable")
{
	WHEN("Both variables don't exist")
	{
		Calculator calculator;
		THEN("Return FALSE, no define")
		{
			Identifier identifier1 = "x";
			Identifier identifier2 = "y";
			REQUIRE(!calculator.IsIdentifierExist(identifier1));
			REQUIRE(!calculator.IsIdentifierExist(identifier2));

			REQUIRE(!calculator.AssignVariable(identifier1, identifier2));
		}
	}
	WHEN("First variable exists, but second doesn't")
	{
		Calculator calculator;
		THEN("Return FALSE, no define")
		{
			Identifier identifier1 = "x";
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.IsIdentifierExist(identifier1));
			Identifier identifier2 = "y";
			REQUIRE(!calculator.IsIdentifierExist(identifier2));

			REQUIRE(!calculator.AssignVariable(identifier1, identifier2));
		}
	}
	WHEN("First variable doesn't exist, but second does")
	{
		Calculator calculator;
		THEN("First variable is now existing and its value = second variable's value")
		{
			Identifier identifier1 = "x";
			REQUIRE(!calculator.IsIdentifierExist(identifier1));
			Identifier identifier2 = "y";
			REQUIRE(calculator.DefineVariable(identifier2));
			REQUIRE(calculator.IsIdentifierExist(identifier2));
			Value value2 = 5.53241;
			REQUIRE(calculator.AssignVariable(identifier2, value2));

			REQUIRE(calculator.AssignVariable(identifier1, identifier2));
			REQUIRE(calculator.IsIdentifierExist(identifier1));
			REQUIRE(calculator.GetVariableValue(identifier1).value() == value2);
		}
	}
	WHEN("First variable exist and so does second one")
	{
		Calculator calculator;
		THEN("First variable's value is now second variable's value")
		{
			Identifier identifier1 = "x";
			Value value1 = 1415.53241;
			REQUIRE(calculator.DefineVariable(identifier1));
			REQUIRE(calculator.IsIdentifierExist(identifier1));
			REQUIRE(calculator.AssignVariable(identifier1, value1));
			REQUIRE(calculator.GetVariableValue(identifier1).value() == value1);

			Identifier identifier2 = "y";
			Value value2 = 5.53241;
			REQUIRE(calculator.DefineVariable(identifier2));
			REQUIRE(calculator.IsIdentifierExist(identifier2));
			REQUIRE(calculator.AssignVariable(identifier2, value2));
			REQUIRE(calculator.GetVariableValue(identifier2).value() == value2);


			REQUIRE(calculator.AssignVariable(identifier1, identifier2));
			REQUIRE(calculator.GetVariableValue(identifier2).value() == value2);
			
		}
	}
}