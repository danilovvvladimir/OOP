#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../StringList/CStringList.h"

SCENARIO("Testing Constructors")
{
	WHEN("Constructed by default constructor")
	{
		THEN("List is empty")
		{
			CStringList lst = CStringList();
			REQUIRE(lst.IsEmpty());
			REQUIRE(lst.GetSize() == 0);
		}
	}
	WHEN("Constructed by copying constructor")
	{
		THEN("List is the same as the original one")
		{
			CStringList lst1 = CStringList();
			lst1.PushBack("Hello");

			CStringList lst2 = CStringList(lst1);
			REQUIRE(lst2.GetSize() == lst1.GetSize());
		}
	}
	WHEN("Constructed by moved-out constructor")
	{
		THEN("List is the same as moved-out list was")
		{
			CStringList lst1 = CStringList();
			lst1.PushBack("Hello");

			CStringList lst2 = CStringList(std::move(lst1));
			REQUIRE(lst2.GetSize() == 1);

			REQUIRE(lst1.GetSize() == 0);
		}
	}
}

SCENARIO("Testing Push elements")
{
	WHEN("PushBack")
	{
		THEN("Successfully pushed back")
		{
			CStringList lst;
			lst.PushBack("1");
			lst.PushBack("2");
			lst.PushBack("3");

			REQUIRE(lst.GetSize() == 3);
		}
	}
	WHEN("PushFront")
	{
		THEN("Successfully pushed back")
		{
			CStringList lst;
			lst.PushFront("1");
			lst.PushFront("2");
			lst.PushFront("3");

			REQUIRE(lst.GetSize() == 3);
		}
	}
}

SCENARIO("Testing IsEmpty")
{
	WHEN("List is empty")
	{
		THEN("Return true")
		{
			CStringList lst;
			REQUIRE(lst.IsEmpty());
		}
	}

	WHEN("List is not empty")
	{
		THEN("Return false")
		{
			CStringList lst;
			lst.PushFront("1");
			lst.PushFront("2");
			lst.PushFront("3");

			REQUIRE(!(lst.IsEmpty()));
		}
	}
}

SCENARIO("Testing Insertions")
{
	WHEN("Insert in the beginning of empty list")
	{
		THEN("Return true")
		{
			CStringList lst;
			std::string placedStr = "hello";
			lst.Insert(lst.begin(), placedStr);

			REQUIRE(*lst.begin() == placedStr);
			REQUIRE(lst.GetSize() == 1);
		}
	}

	WHEN("Insert in the beginning of non empty list")
	{
		THEN("Return false")
		{
			CStringList lst;
			std::string placedStr = "hello";

			lst.Insert(lst.begin(), "123");
			lst.Insert(lst.begin(), placedStr);

			REQUIRE(*lst.begin() == placedStr);
			REQUIRE(lst.GetSize() == 2);
		}
	}

	WHEN("Insert in the end of empty list")
	{
		THEN("Return true")
		{
			CStringList lst;
			std::string placedStr = "hello";
			lst.Insert(lst.end(), placedStr);

			REQUIRE(*--lst.end() == placedStr);
			REQUIRE(lst.GetSize() == 1);
		}
	}

	WHEN("Insert in the end of non empty list")
	{
		THEN("Return false")
		{
			CStringList lst;
			std::string placedStr = "hello";

			lst.Insert(lst.end(), "123");
			lst.Insert(lst.end(), placedStr);

			REQUIRE(*--lst.end() == placedStr);
			REQUIRE(lst.GetSize() == 2);
		}
	}
}

SCENARIO("Testing Erase")
{
	WHEN("Erase empty list")
	{
		THEN("Throw out of range error")
		{
			CStringList lst;
			REQUIRE(lst.GetSize() == 0);
			REQUIRE_THROWS_AS(lst.Erase(lst.begin()), std::out_of_range);
			
		}
	}
	WHEN("Erase existing element in list")
	{
		THEN("Erased successfully")
		{
			CStringList lst;
			lst.PushBack("sor");
			REQUIRE(lst.GetSize() == 1);
				
			lst.Erase(lst.begin());
			REQUIRE(lst.GetSize() == 0);
		}
	}
	WHEN("Erase out of range element in list")
	{
		THEN("Erased successfully")
		{
			CStringList lst;
			lst.PushBack("sor");
			REQUIRE(lst.GetSize() == 1);

			REQUIRE_THROWS_AS(lst.Erase(++lst.begin()), std::out_of_range);
			REQUIRE(lst.GetSize() == 1);
		}
	}
}

SCENARIO("Testing Clear")
{
	CStringList lst;
	lst.PushFront("1");
	lst.PushFront("2");
	lst.PushFront("3");

	REQUIRE(lst.GetSize() == 3);
	lst.Clear();

	REQUIRE(lst.GetSize() == 0);
}

SCENARIO("Testing operator= copying")
{
	CStringList lst;
	lst.PushFront("Hello ");
	lst.PushFront("world");

	CStringList lstCopy = lst;
	REQUIRE(lstCopy.GetSize() == lst.GetSize());
}

SCENARIO("Testing operator= move-out")
{
	CStringList lstMovedOut;
	lstMovedOut.PushFront("Hello ");
	lstMovedOut.PushFront("world");
	size_t lengthMoveOut = lstMovedOut.GetSize();

	CStringList lst = std::move(lstMovedOut);
	REQUIRE(lst.GetSize() == lengthMoveOut);
	REQUIRE(lstMovedOut.GetSize() == 0);
}

SCENARIO("Testing iterators")
{
	CStringList lst;
	lst.PushBack("1");
	lst.PushBack("2");
	lst.PushBack("3");

	WHEN("Testing ++ and -- operators of iterator")
	{
		auto it = lst.cbegin();
		REQUIRE(*it == "1");
		it++;
		REQUIRE(*it == "2");
		++it;
		REQUIRE(*it == "3");
		it--;
		REQUIRE(*it == "2");
		--it;
		REQUIRE(*it == "1");
	}

	WHEN("Testing cbegin")
	{
		auto it = lst.cbegin();
		REQUIRE(*it == "1");
	}

	WHEN("Testing cend")
	{
		auto it = lst.cend();
		--it;
		REQUIRE(*it == "3");
	}

	WHEN("Testing begin")
	{
		auto it = lst.begin();
		REQUIRE(*it == "1");
	}

	WHEN("Testing end")
	{
		auto it = lst.end();
		--it;
		REQUIRE(*it == "3");
	}

	WHEN("Testing rcbegin")
	{
		auto it = lst.crbegin();
		REQUIRE(*it == "3");
	}

	WHEN("Testing rcend")
	{
		auto it = lst.crend();
		--it;
		REQUIRE(*it == "1");
	}

	WHEN("Testing rbegin")
	{
		auto it = lst.rbegin();
		REQUIRE(*it == "3");
	}

	WHEN("Testing rend")
	{
		auto it = lst.rend();
		--it;
		REQUIRE(*it == "1");
	}

	WHEN("dereference iterator")
	{
		auto it = lst.begin();
		REQUIRE(*it == "1");
		*it = "now definitely not 1";
		REQUIRE(*it == "now definitely not 1");
		*it = "1";
		REQUIRE(*it == "1");
	}
}

SCENARIO("Test range-based for")
{
	std::string str1("Grind");

	std::string str2("Never");
	std::string str3("Stops");
	std::ostringstream outputStream;

	CStringList lst;

	lst.PushBack(str1);
	lst.PushBack(str2);
	lst.PushBack(str3);
	REQUIRE(lst.GetSize() == 3);

	for (auto& element : lst)
	{
		outputStream << element;
	}

	REQUIRE(outputStream.str() == "GrindNeverStops");
}