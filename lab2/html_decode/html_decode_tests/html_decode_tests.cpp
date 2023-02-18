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
	WHEN("There is 1 html entity in input stream: &lt;h1&gt;")
	{
		THEN("There is 1 html tag in output stream: <h1>")
		{
			std::istringstream input("&lt;h1&gt;Hello World!&lt;/h1&gt;");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "<h1>Hello World!</h1>\n");
		}
	}
	WHEN("There are several html entities in input stream: &lt;&lt;&lt;It workes&gt;&gt;&gt;")
	{
		THEN("There are several html entities in output stream: <<<It workes>>>")
		{
			std::istringstream input("&lt;&lt;&lt;It workes&gt;&gt;&gt;");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "<<<It workes>>>\n");
		}
	}
	WHEN("There are several html entities with single & in input stream: &lt;&lt;&lt;& - this is single amp&gt;&gt;&gt;")
	{
		THEN("There are several html entities with single & in output stream: <<<& - this is single amp>>>")
		{
			std::istringstream input("&lt;&lt;&lt;& - this is single amp&gt;&gt;&gt;");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "<<<& - this is single amp>>>\n");
		}
	}
}