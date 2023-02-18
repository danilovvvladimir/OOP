#pragma once
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>
#include <string>

struct HTMLEntity;
HTMLEntity DecodeString(const std::string& str);
std::string HtmlDecodeText(std::string& inputText);
void HtmlDecode(std::istream& input, std::ostream& output);