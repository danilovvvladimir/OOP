#pragma once
#include <iostream>
#include <regex>
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	UNKNOW_PROTOCOL
};

Protocol StringToProtocol(std::string const& stringProtocol);
int ProtocolToPort(Protocol protocol);
bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
void PrintUrlInfo(std::string const& url, std::ostream& output);
void HandleUrlParsing(std::istream& input, std::ostream& output);
