#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HttpUrl/CHttpUrl.h"
#include <sstream>

const int MIN_PORT = 10;
const int MAX_PORT = 65535;

SCENARIO("Testing Constructors with string")
{
	WHEN("Construct HttpUrl with string of correct url")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://vk.com"));
		}
	}
	WHEN("Construct HttpUrl with string of correct url (with complicated domain)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://vk.com/news/somenewarticle/something"));
		}
	}
	WHEN("Construct HttpUrl with string of correct url (and with document)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://vk.com/photo.jpg"));
		}
	}
	WHEN("Construct HttpUrl with string of correct url (and with MIN available port)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://vk.com:" + std::to_string(MIN_PORT) + "/photo.jpg"));
		}
	}
	WHEN("Construct HttpUrl with string of correct url (and with MAX available port)")
	{
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://vk.com:"+ std::to_string(MAX_PORT) +"/photo.jpg"));
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (no protocol)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("//vk.com/fruityflunt"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (no domain)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (wrong protocol)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("ftp://vk.com/fruityflunt"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (wrong domain)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://git hub"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (wrong document)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://github.com/page 123"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (port is not a number)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://github.com:string"), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (port is less than MIN available port)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://github.com:"+(MIN_PORT-1)), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with string of incorrect url (port is greater than MAX available port)")
	{
		THEN("HttpUrl is not created")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://github.com:" + (MAX_PORT + 1)), CUrlParsingError);
		}
	}
}

SCENARIO("Testing Constructors with protocol, domain, document")
{
	Protocol protocol;
	std::string domain;
	std::string document;
	WHEN("Construct HttpUrl with correct values and empty document")
	{
		protocol = Protocol::HTTP;
		domain = "vk.com";
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol));
		}
	}
	WHEN("Construct HttpUrl with correct values and valued document")
	{
		protocol = Protocol::HTTPS;
		domain = "vk.com";
		document = "main/sogspg.jpg";
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol));
		}
	}
	WHEN("Construct HttpUrl with incorrect domain")
	{
		protocol = Protocol::HTTP;
		domain = "vk  .com";
		THEN("HttpUrl is created")
		{
			REQUIRE_THROWS_AS(CHttpUrl(domain, document, protocol), CUrlParsingError);
		}
	}
	WHEN("Construct HttpUrl with incorrect document")
	{
		protocol = Protocol::HTTPS;
		domain = "vk.com";
		document = "ma in /sogspg.jpg";
		THEN("HttpUrl is created")
		{
			REQUIRE_THROWS_AS(CHttpUrl(domain, document, protocol), CUrlParsingError);
		}
	}
}

SCENARIO("Testing Constructors with protocol, domain, document and PORT")
{
	Protocol protocol;
	std::string domain;
	std::string document;
	Port port;
	WHEN("Construct HttpUrl with correct values and random port")
	{
		protocol = Protocol::HTTP;
		domain = "vk.com";
		port = 52532;
		THEN("HttpUrl is created")
		{
			REQUIRE_NOTHROW(CHttpUrl(domain, document, protocol, MIN_PORT));
		}
	}
}

SCENARIO("Testing Getters")
{
	Protocol protocol = Protocol::HTTPS;
	std::string domain = "vk.com";
	Port port = 4554;
	std::string document = "/news/somenewarticle/something.jpg";
	std::string correctStringUrl = CHttpUrl::ParseProtocolToString(protocol)+ "://" + domain + ":" + std::to_string(port) + document;

	CHttpUrl correctUrl(domain, document, protocol, port);
	WHEN("Testing GetProtocol")
	{
		REQUIRE(correctUrl.GetProtocol() == protocol);
	}
	WHEN("Testing GetDomain")
	{
		REQUIRE(correctUrl.GetDomain() == domain);
	}
	WHEN("Testing GetDocument")
	{
		REQUIRE(correctUrl.GetDocument() == document);
	}
	WHEN("Testing GetPort")
	{
		REQUIRE(correctUrl.GetPort() == port);
	}
	WHEN("Testing GetURL")
	{
		REQUIRE(correctUrl.GetURL() == correctStringUrl);
	}
}
