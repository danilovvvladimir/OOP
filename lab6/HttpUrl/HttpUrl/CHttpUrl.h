#pragma once

#include "CUrlParsingError.h"
#include <string>
#include <algorithm>
#include <regex>
#include <cctype>

enum class Protocol
{
	HTTP,
	HTTPS
};

using Port = unsigned short;

class CHttpUrl
{
	
public:
	// ==> Constructors <==
	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP
	);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		Port port
	);

	// ==> Getters <==
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	Port GetPort() const;

	static std::string ParseProtocolToString(Protocol protocol);

private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;
};
