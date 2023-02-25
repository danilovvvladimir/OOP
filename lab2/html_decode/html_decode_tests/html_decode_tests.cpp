#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../html_decode/HtmlDecode.h"

SCENARIO("Decode Lines")
{
	std::ostringstream output;
	WHEN("Line is empty")
	{
		THEN("Line doesn't change")
		{
			std::istringstream input("");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "\n");
		}
	}
	WHEN("There is no HTML entities")
	{
		THEN("Line doesn't change")
		{
			std::istringstream input("There are no html entities");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "There are no html entities\n");
		}
	}
	WHEN("There is 1 html entity in istream: &lt;h1&gt;")
	{
		THEN("There is 1 html tag in ostream: <h1>")
		{
			std::istringstream input("&lt;h1&gt;Hello World!&lt;/h1&gt;");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "<h1>Hello World!</h1>\n");
		}
	}
	WHEN("There are several html entities in istream: &lt;&lt;&lt;It workes&gt;&gt;&gt;")
	{
		THEN("There are several html entities in ostream: <<<It workes>>>")
		{
			std::istringstream input("&lt;&lt;&lt;It workes&gt;&gt;&gt;");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "<<<It workes>>>\n");
		}
	}
	WHEN("There are several html entities with single & in istream: &lt;&lt;&lt;& - this is single amp&gt;&gt;&gt;")
	{
		THEN("There are several html entities with single & in ostream: <<<& - this is single amp>>>")
		{
			std::istringstream input("&lt;&lt;&lt;& - this is single amp&gt;&gt;&gt;");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "<<<& - this is single amp>>>\n");
		}
	}
	WHEN("There are several lines in istream")
	{
		THEN("Several lines in ostream")
		{
			std::istringstream input("&lt;h1&gt;Hello World!&lt;/h1&gt;\n&lt;h2&gt;It workes!&lt;/h2&gt;");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "<h1>Hello World!</h1>\n<h2>It workes!</h2>\n");
		}
	}
}