#include "UrlParser.h"


std::string StringToLowerCase(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) {
			return std::tolower(c);
		});
	return result;
}

Protocol StringToProtocol(std::string const& stringProtocol)
{
	if (stringProtocol == "http")
		return Protocol::HTTP;
	if (stringProtocol == "https")
		return Protocol::HTTPS;
	if (stringProtocol == "ftp")
		return Protocol::FTP;

	return Protocol::UNKNOW_PROTOCOL;
}

int ProtocolToPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
	{
		return HTTP_PORT;
	}
	case Protocol::HTTPS:
	{
		return HTTPS_PORT;
	}
	case Protocol::FTP:
	{
		return FTP_PORT;
	}
	default:
		return INVALID_PORT_CODE;
	}
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::cmatch result;
	std::string lowerCasedURL = StringToLowerCase(url);
	std::regex urlRegexpression("(https|http|ftp)"
								"://"
								"([\\w-]{1,63}(?:\\.[\\w-]{1,63})?)+"
								"(?::(\\d{1,5}))?"
								"(?:(?:/)([\\S]*))?");
	if (std::regex_match(lowerCasedURL.c_str(), result, urlRegexpression))
	{
		protocol = StringToProtocol(result[1]);
		host = result[2];
		port = GetPort(port, result[3], protocol);

		if (port == INVALID_PORT_CODE)
		{
			return false;
		}

		document = result[4];
		return true;
	}
	return false;
}

int GetPort(int port, std::string result, Protocol& protocol)
{
	if (result != "")
	{
		port = std::stoi(result);
		if (port < PORT_MIN || port > PORT_MAX)
		{
			return INVALID_PORT_CODE;
		}
	}
	else
	{
		port = ProtocolToPort(protocol);
	}
	return port;
}

void PrintUrlInfo(std::string const& url, std::ostream& output)
{
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;

	if (ParseURL(url, protocol, port, host, document))
	{
		output << url << std::endl;
		output << "HOST: " << host << std::endl;
		output << "PORT: " << port << std::endl;
		output << "DOC: " << document << std::endl;
	}
	else
	{
		output << "This is not url" << std::endl;
	}
}

void HandleUrlParsing(std::istream& input, std::ostream& output)
{
	std::string url;
	while (!input.eof())
	{
		std::getline(input, url);
		PrintUrlInfo(url, output);
	}
}