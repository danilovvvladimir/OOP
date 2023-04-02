#include "CUrlParsingError.h"

const std::string INVALID_URL_MESSAGE = "Invalid Url";
const std::string INVALID_PORT_MESSAGE = "Invalid port. Port must be number in this interval: 1 <= Port <= 65565";
const std::string INVALID_PROTOCOL_MESSAGE = "Can't create url with invalid protocol. Protocol must be: HTTP / HTTPS";
const std::string INVALID_DOMAIN_MESSAGE = "Can't create url with invalid domain. Domain mustn't be empty";

CUrlParsingError CUrlParsingError::InvalidUrl()
{
	return CUrlParsingError(INVALID_URL_MESSAGE);
}

CUrlParsingError CUrlParsingError::InvalidPort()
{
	return CUrlParsingError(INVALID_PORT_MESSAGE);
}

CUrlParsingError CUrlParsingError::InvalidProtocol()
{
	return CUrlParsingError(INVALID_PROTOCOL_MESSAGE);
}

CUrlParsingError CUrlParsingError::InvalidDomain()
{
	return CUrlParsingError(INVALID_DOMAIN_MESSAGE);
}

CUrlParsingError::CUrlParsingError(std::string const& message)
	: std::invalid_argument(message)
{
}
