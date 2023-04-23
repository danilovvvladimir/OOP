#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CMyList/CMyList.hpp"

#include <sstream>
#include <string>

SCENARIO("Testing Constructors")
{
	WHEN("Constructed by default constructor")
	{
		THEN("List is empty")
		{
			CMyList<std::string> lst = CMyList<std::string>();
			REQUIRE(lst.IsEmpty());
			REQUIRE(lst.GetSize() == 0);
		}
	}
	WHEN("Constructed by copying constructor")
	{
		THEN("List is the same as the original one")
		{
			CMyList<std::string> lst1 = CMyList<std::string>();
			lst1.PushBack("Hello");

			CMyList<std::string> lst2 = CMyList<std::string>(lst1);
			REQUIRE(lst2.GetSize() == lst1.GetSize());
		}
	}
}

SCENARIO("Testing Push elements")
{
	WHEN("PushBack")
	{
		THEN("Successfully pushed back")
		{
			CMyList<std::string> lst;
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
			CMyList<std::string> lst;
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
			CMyList<std::string> lst;
			REQUIRE(lst.IsEmpty());
		}
	}

	WHEN("List is not empty")
	{
		THEN("Return false")
		{
			CMyList<std::string> lst;
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
			CMyList<std::string> lst;
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
			CMyList<std::string> lst;
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
			CMyList<std::string> lst;
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
			CMyList<std::string> lst;
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
			CMyList<std::string> lst;
			REQUIRE(lst.GetSize() == 0);
			REQUIRE_THROWS_AS(lst.Erase(lst.begin()), std::out_of_range);
		}
	}
	WHEN("Erase existing element in list")
	{
		THEN("Erased successfully")
		{
			CMyList<std::string> lst;
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
			CMyList<std::string> lst;
			lst.PushBack("sor");
			REQUIRE(lst.GetSize() == 1);

			REQUIRE_THROWS_AS(lst.Erase(++lst.begin()), std::out_of_range);
			REQUIRE(lst.GetSize() == 1);
		}
	}
}

SCENARIO("Testing Clear")
{
	CMyList<std::string> lst;
	lst.PushFront("1");
	lst.PushFront("2");
	lst.PushFront("3");

	REQUIRE(lst.GetSize() == 3);
	lst.Clear();

	REQUIRE(lst.GetSize() == 0);
}

SCENARIO("Testing operator= copying")
{
	CMyList<std::string> lst;
	lst.PushFront("Hello ");
	lst.PushFront("world");

	CMyList<std::string> lstCopy = lst;
	REQUIRE(lstCopy.GetSize() == lst.GetSize());
}

SCENARIO("Testing iterators")
{
	CMyList<std::string> lst;
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

	CMyList<std::string> lst;

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

SCENARIO("Clear after creation")
{
	CMyList<std::string> lst;
	lst.PushBack("abc");
	lst.Clear();

	REQUIRE(lst.IsEmpty());

	lst.PushBack("def");

	REQUIRE(!lst.IsEmpty());
}

SCENARIO("Testing int List")
{
	CMyList<int> lst;
	int firstN = 100;
	int secondN = 200;
	int thirdN = 300;

	// ===> Testing Adding <===
	lst.Insert(lst.begin(), secondN);
	lst.PushBack(thirdN);
	lst.PushFront(firstN);
	REQUIRE(lst.GetSize() == 3);

	// ===> Testing iterators stl algorithms <===
	std::ostringstream outputStream;
	for (auto& element : lst)
	{
		outputStream << element;
	}
	REQUIRE(outputStream.str() == "100200300");

	// ===> Testing removing <===
	lst.Erase(lst.begin());
	REQUIRE(lst.GetSize() == 2);

	// ===> Testing clear <===
	lst.Clear();
	REQUIRE(lst.IsEmpty());

	lst.PushBack(100500);

	// ===> Testing copying <===
	CMyList<int> newLst(lst);
	REQUIRE(newLst.GetSize() == lst.GetSize());
	auto itLst = lst.begin();
	auto itNewLst = newLst.begin();
	REQUIRE(*itLst == *itNewLst);
}