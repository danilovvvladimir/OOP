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