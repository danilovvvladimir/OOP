#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <cctype>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	UNKNOW_PROTOCOL
};

const int PORT_MIN = 1;
const int PORT_MAX = 65535;
const int HTTP_PORT = 80;
const int HTTPS_PORT = 443;
const int FTP_PORT = 21;
const int INVALID_PORT_CODE = 0;

Protocol StringToProtocol(std::string const& stringProtocol);
int ProtocolToPort(Protocol protocol);
bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
void PrintUrlInfo(std::string const& url, std::ostream& output);
void HandleUrlParsing(std::istream& input, std::ostream& output);
int GetPort(int port, std::string result, Protocol& protocol);
