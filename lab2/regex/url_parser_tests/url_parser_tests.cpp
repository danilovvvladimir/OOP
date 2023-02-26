#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../regex/UrlParser.h"

SCENARIO("Testing different protocols")
{
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;
	WHEN("correct protocol ftp")
	{
		std::string url = "ftp://vk.com/";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::FTP);
		REQUIRE(host == "vk.com");
		REQUIRE(port == FTP_PORT);
		REQUIRE(document == "");
	}
	WHEN("correct protocol http")
	{
		std::string url = "http://vk.com/";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTP);
		REQUIRE(host == "vk.com");
		REQUIRE(port == HTTP_PORT);
		REQUIRE(document == "");
	}
	WHEN("correct protocol https")
	{
		std::string url = "https://vk.com/";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(host == "vk.com");
		REQUIRE(port == HTTPS_PORT);
		REQUIRE(document == "");
	}
	WHEN("incorrect protocol ftppp")
	{
		std::string url = "ftppp://vk.com/";
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}
	WHEN("empty protocol")
	{
		std::string url = "vk.com/";
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}
}
SCENARIO("Testing different hosts")
{
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;
	WHEN("correct host vk.com")
	{
		std::string url = "https://vk.com/";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(host == "vk.com");
		REQUIRE(port == HTTPS_PORT);
		REQUIRE(document == "");
	}
	WHEN("correct host localhost")
	{
		std::string url = "https://localhost/";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(host == "localhost");
		REQUIRE(port == HTTPS_PORT);
		REQUIRE(document == "");
	}
	WHEN("incorrect host")
	{
		std::string url = "https://.com/";
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}
}
SCENARIO("Testing different ports")
{
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;
	WHEN("correct port 1")
	{
		std::string url = "https://vk.com:1/";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(host == "vk.com");
		REQUIRE(port == 1);
		REQUIRE(document == "");
	}
	WHEN("correct port 65535")
	{
		std::string url = "https://vk.com:65535/";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(host == "vk.com");
		REQUIRE(port == 65535);
		REQUIRE(document == "");
	}
	WHEN("incorrect port 0")
	{
		std::string url = "https://vk.com:0/";
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}
	WHEN("incorrect port 65536")
	{
		std::string url = "https://vk.com:65536";
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}
	WHEN("incorrect port wwwww")
	{
		std::string url = "https://vk.com:wwwww";
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}
}

SCENARIO("Testing correct urls")
{
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;
	WHEN("correct url, no port, no doc")
	{
		std::string url = "https://vk.com";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(host == "vk.com");
		REQUIRE(port == HTTPS_PORT);
		REQUIRE(document == "");
	}
	WHEN("correct url, no doc")
	{
		std::string url = "https://vk.com:8000";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(host == "vk.com");
		REQUIRE(port == 8000);
		REQUIRE(document == "");
	}
	WHEN("correct url, no port")
	{
		std::string url = "https://vk.com/albums146463253?z=photo146463253_457286247%2Fphotos146463253";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(host == "vk.com");
		REQUIRE(port == HTTPS_PORT);
		REQUIRE(document == "albums146463253?z=photo146463253_457286247%2fphotos146463253");
	}
	WHEN("correct url")
	{
		std::string url = "https://vk.com:8000/albums146463253?z=photo146463253_457286247%2Fphotos146463253";
		REQUIRE(ParseURL(url, protocol, port, host, document));
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(host == "vk.com");
		REQUIRE(port == 8000);
		REQUIRE(document == "albums146463253?z=photo146463253_457286247%2fphotos146463253");
	}
}
