#pragma once

#include <string>

class CUrlParsingError : public std::invalid_argument
{
public:
	static CUrlParsingError InvalidUrl();
	static CUrlParsingError InvalidPort();
	static CUrlParsingError InvalidProtocol();
	static CUrlParsingError InvalidDomain();

private:
	CUrlParsingError(std::string const& message);
};