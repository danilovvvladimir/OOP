#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MyString/CMyString.h"
#include <sstream>

SCENARIO("Testing Constructors")
{
	WHEN("Default constructor")
	{
		THEN("MyString is empty")
		{
			CMyString mystr = CMyString();
			REQUIRE(mystr.GetLength() == 0);
			REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
		}
	}
	WHEN("C string constructor")
	{
		THEN("MyString contains C string")
		{
			const char* cStr = "Hello world";
			CMyString mystr = CMyString(cStr);

			REQUIRE(mystr.GetLength() == strlen(cStr));
			REQUIRE(strcmp(mystr.GetStringData(), cStr) == 0);
		}
	}
	WHEN("C string constructor containing nullish string code")
	{
		THEN("MyString contains C string")
		{
			const char* cStr = "Hello \0world";
			CMyString mystr = CMyString(cStr);

			REQUIRE(mystr.GetLength() == strlen(cStr));
			REQUIRE(strcmp(mystr.GetStringData(), cStr) == 0);
		}
	}
	WHEN("C string with string length constructor")
	{
		THEN("MyString contains C string")
		{
			const char* cStr = "Hello world";
			int cStrLength = strlen(cStr);
			CMyString mystr = CMyString(cStr, cStrLength);

			REQUIRE(mystr.GetLength() == cStrLength);
			REQUIRE(strcmp(mystr.GetStringData(), cStr) == 0);
		}
	}
	WHEN("Copy constructor")
	{
		THEN("MyString1 contains same string as MyString2")
		{
			const char* cStr = "Hello world";
			int cStrLength = strlen(cStr);

			CMyString mystr1 = CMyString(cStr, cStrLength);
			CMyString mystr2 = CMyString(mystr1);

			REQUIRE(mystr1.GetLength() == mystr2.GetLength());
			REQUIRE(strcmp(mystr1.GetStringData(), mystr2.GetStringData()) == 0);
		}
	}
	WHEN("STL string constructor")
	{
		THEN("MyString contains same string as STL string")
		{
			std::string stlString = "This is STL string";

			CMyString mystr1 = CMyString(stlString);

			REQUIRE(mystr1.GetLength() == stlString.size());
			REQUIRE(strcmp(mystr1.GetStringData(), stlString.c_str()) == 0);
		}
	}
	WHEN("STL string constructor containing nullish string code")
	{
		THEN("MyString contains same \0 string as STL string")
		{
			std::string stlString = "This is STL string";

			CMyString mystr1 = CMyString(stlString);

			REQUIRE(mystr1.GetLength() == stlString.size());
			REQUIRE(strcmp(mystr1.GetStringData(), stlString.c_str()) == 0);
		}
	}

}

SCENARIO("Testing Clear")
{
	WHEN("MyString is empty")
	{
		THEN("MyString is still empty")
		{
			CMyString mystr;
			mystr.Clear();

			REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
			REQUIRE(mystr.GetLength() == 0);
		}
	}
	WHEN("MyString is not empty")
	{
		THEN("MyString is empty")
		{
			CMyString mystr("This is STL string");
			mystr.Clear();

			REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
			REQUIRE(mystr.GetLength() == 0);
		}
	}
}

SCENARIO("Testing GetLength")
{
	WHEN("MyString is empty")
	{
		THEN("Length is 0")
		{
			CMyString mystr;
			REQUIRE(mystr.GetLength() == 0);
		}
	}
	WHEN("MyString is not empty")
	{
		THEN("Length is correct size of string")
		{
			std::string stlString("STL");
			CMyString mystr(stlString);

			REQUIRE(mystr.GetLength() == stlString.size());
		}
	}
}

SCENARIO("Testing GetStringDate")
{
	WHEN("MyString is empty")
	{
		THEN("Data is empty string")
		{
			CMyString mystr;
			REQUIRE(strcmp(mystr.GetStringData(), "") == 0);
		}
	}

	WHEN("MyString is not empty")
	{
		THEN("Data is MyString data")
		{
			std::string stlString("STL");
			CMyString mystr(stlString);

			REQUIRE(strcmp(mystr.GetStringData(), stlString.c_str()) == 0);
		}
	}
}

SCENARIO("Testing SubString")
{
	WHEN("Method is called correctly")
	{
		THEN("return correct substring")
		{
			CMyString mystr("Hello world");
			CMyString substring = mystr.SubString(1, 5);

			REQUIRE(strcmp(substring.GetStringData(), "ello ") == 0);
		}
	}

	WHEN("Method is called correctly with nullish string code")
	{
		THEN("return correct substring")
		{
			CMyString sNulls("Hello\0, world", 13);

			auto const subString = sNulls.SubString(0, 8);

			REQUIRE(std::strcmp(subString.GetStringData(), "Hello\0, ") == 0);
		}
	}

	WHEN("Method is called incorrectly: <start> is greater than string length")
	{
		THEN("throw exception")
		{
			std::ostringstream outputStream;
			CMyString mystr("Hello world");

			try
			{
				CMyString substring = mystr.SubString(mystr.GetLength() + 1, 5);
			}
			catch (const std::exception& e)
			{
				outputStream << e.what();
			}
			REQUIRE(outputStream.str() == "<start> index is out of string range");
		}
	}

	WHEN("Method is called incorrectly: <length> is greater than string length - <start> index")
	{
		THEN("throw exception")
		{
			std::ostringstream outputStream;
			CMyString mystr("Hello world");

			try
			{
				CMyString substring = mystr.SubString(0, mystr.GetLength() + 1);
			}
			catch (const std::exception& e)
			{
				outputStream << e.what();
			}
			REQUIRE(outputStream.str() == "<length> is out of range");
		}
	}
}

SCENARIO("Testing << operator")
{
	WHEN("MyString has nullish code in the middle")
	{
		THEN("Put MyString Data in outputStream")
		{
			std::ostringstream outputStream;

			CMyString mystr("This is \0 nullish code symbol");
			outputStream << mystr;
			REQUIRE(outputStream.str() == mystr.GetStringData());
		}
	}
	WHEN("MyString is empty")
	{
		THEN("Put MyString Data in outputStream")
		{
			std::ostringstream outputStream;

			CMyString mystr;
			outputStream << mystr;
			REQUIRE(outputStream.str() == mystr.GetStringData());
		}
	}
	WHEN("MyString is not empty")
	{
		THEN("Put MyString Data in outputStream")
		{
			std::ostringstream outputStream;

			CMyString mystr("This string is designed for << test");
			outputStream << mystr;
			REQUIRE(outputStream.str() == mystr.GetStringData());
		}
	}
}

SCENARIO("Testing operator +=")
{
	WHEN("Two CMyStrings are empty")
	{
		THEN("First CMyString is empty")
		{
			CMyString str1 = "";
			CMyString str2 = "";

			str1 += str2;
			REQUIRE(strcmp(str1.GetStringData(), "") == 0);
		}
	}
	WHEN("Two CMyStrings are different")
	{
		THEN("CMyString contains first its data and other's data")
		{
			CMyString str1 = "Hello ";
			CMyString str2 = "world!";

			str1 += str2;
			REQUIRE(strcmp(str1.GetStringData(), "Hello world!") == 0);
		}
	}
}

SCENARIO("Testing operator +")
{
	WHEN("Two CMyStrings are empty")
	{
		THEN("First CMyString is empty")
		{
			CMyString str1 = "";
			CMyString str2 = "";

			CMyString str3 = str1 + str2;
			REQUIRE(strcmp(str3.GetStringData(), "") == 0);
		}
	}
	WHEN("Combaining two CMyStrings")
	{
		THEN("Result CMyString contains data of both CMyStrings")
		{
			CMyString str1 = "Hello ";
			CMyString str2 = "world!";

			CMyString str3 = str1 + str2;
			REQUIRE(strcmp(str3.GetStringData(), "Hello world!") == 0);
		}
	}
	WHEN("Combaining CMyString and std::string")
	{
		THEN("Result CMyString contains data of both CMyString and std::string")
		{
			std::string str1 = "Hello ";
			CMyString str2 = "world!";

			CMyString str3 = str1 + str2;
			REQUIRE(strcmp(str3.GetStringData(), "Hello world!") == 0);
		}
	}
	WHEN("Combaining CMyString and const char*")
	{
		THEN("Result CMyString contains data of both CMyString and const char*")
		{
			CMyString str2 = "world!";

			CMyString str3 = "Hello " + str2;
			REQUIRE(strcmp(str3.GetStringData(), "Hello world!") == 0);
		}
	}
}

SCENARIO("Testing operator ==")
{
	WHEN("Two CMyStrings are equal")
	{
		THEN("return true")
		{
			CMyString str1 = "Hi";
			CMyString str2 = "Hi";

			REQUIRE(str1 == str2);
		}
	}
	WHEN("Two CMyStrings are different")
	{
		THEN("return false")
		{
			CMyString str1 = "Hi";
			CMyString str2 = "Not Hi";

			REQUIRE(!(str1 == str2));
		}
	}
}

SCENARIO("Testing operator !=")
{
	WHEN("Two CMyStrings are equal")
	{
		THEN("return false")
		{
			CMyString str1 = "Hi";
			CMyString str2 = "Hi";

			REQUIRE(!(str1 != str2));
		}
	}

	WHEN("Two CMyStrings are different")
	{
		THEN("return true")
		{
			CMyString str1 = "Hi";
			CMyString str2 = "Definitely Not Hi";

			REQUIRE(str1 != str2);
		}
	}
}

SCENARIO("Testing >, <, >=, <= operators")
{
	WHEN("CMyStrings are equal")
	{
		CMyString str1 = "Hi";
		CMyString str2 = "Hi";
		REQUIRE(!(str1 > str2));
		REQUIRE(!(str1 < str2));
		REQUIRE(str1 >= str2);
		REQUIRE(str1 <= str2);
	}
	WHEN("First CMyString is greater(ASCII) than second one")
	{
		CMyString str1 = "aab";
		CMyString str2 = "aaa";
		REQUIRE(str1 > str2);
		REQUIRE(!(str1 < str2));
		REQUIRE(str1 >= str2);
		REQUIRE(!(str1 <= str2));
	}
	WHEN("First CMyString is lesser(ASCII) than second one")
	{
		CMyString str1 = "aaaa";
		CMyString str2 = "aab";
		REQUIRE(!(str1 > str2));
		REQUIRE(str1 < str2);
		REQUIRE(!(str1 >= str2));
		REQUIRE(str1 <= str2);
	}
}