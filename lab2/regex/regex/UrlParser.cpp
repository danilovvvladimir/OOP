#include "UrlParser.h"


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
		return 80;
	}
	case Protocol::HTTPS:
	{
		return 443;
	}
	case Protocol::FTP:
	{
		return 21;
	}
	default:
		return 0;
	}
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::cmatch result;

	std::regex urlRegexpression("(https|http|ftp)"
								"://"
								"([\\w-\\.]+)"
								"(?::(\\d+))?"
								"(?:/([\\S]+))?");

	if (std::regex_match(url.c_str(), result, urlRegexpression))
	{
		protocol = StringToProtocol(result[1]);
		host = result[2];

		if (result[3] != "")
		{
			port = stoi(result[3]);
			if (port < 0 || port > 65535)
			{
				return false;
			}
		}
		else
		{
			port = ProtocolToPort(protocol);
		}

		document = result[4];

		return true;
	}
	return false;
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
	std::string line;
	while (!input.eof())
	{
		std::getline(input, line);
		PrintUrlInfo(line, output);
	}
}