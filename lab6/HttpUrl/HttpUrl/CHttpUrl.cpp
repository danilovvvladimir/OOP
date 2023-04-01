#include "CHttpUrl.h"

const Port HTTP_PORT = 80;
const Port HTTPS_PORT = 443;

CHttpUrl::CHttpUrl(std::string const& url)
{
	// toLower
	// regex full url
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	// isValid domain
	m_domain = domain;
	// parseDomain


	// isValid document
	// parseDocument
	m_document = document;

	// isValid protocol
	// parseProtocol
	m_protocol = protocol;

	// parsePort
	m_port = HTTP_PORT;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, Port port)
	: CHttpUrl(domain, document, protocol)
{
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	std::string url;

	url += ParseProtocolToString(m_protocol);
	url += "/";
	url += m_domain;
	url += (m_port != HTTP_PORT && m_port != HTTPS_PORT) ? ": " + std::to_string(m_port) : "";
	url += m_document;

	return url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

Port CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ParseProtocolToString(Protocol protocol) const
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	default:
		throw std::runtime_error("Can not transform this protocol to string. Unknown protocol");
	}
}
