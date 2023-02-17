#include <algorithm>
#include <iostream>
#include <map>
#include <string>

const char AMP_SYMBOL = '&';

std::map<std::string, char> htmlEntities = { { "&apos;", '\'' }, { "&quot;", '\"' }, { "&lt;", '<' }, { "&gt;", '>' }, { "&amp;", '&' } };

struct HTMLEntity
{
	char symbol;
	size_t length;
};

HTMLEntity DecodeString(const std::string& str)
{
	for (auto htmlEntity : htmlEntities)
	{
		size_t htmlEntityStringSize = htmlEntity.first.size();
		std::string htmlEntityStringCut = str.substr(0, htmlEntityStringSize);

		if (htmlEntityStringCut == htmlEntity.first)
		{
			return HTMLEntity{ htmlEntity.second, htmlEntity.first.size() - 1 };
		}
	}
	return { AMP_SYMBOL, 0 };
}

std::string HtmlDecodeText(std::string& inputText)
{
	std::string resultString;

	for (size_t pos = 0; pos < inputText.size(); pos++)
	{
		auto indexStart = inputText.find(AMP_SYMBOL, pos);
		resultString += inputText.substr(pos, indexStart - pos);

		if (indexStart < inputText.size())
		{
			HTMLEntity decodedEntityMap = DecodeString(inputText.substr(indexStart));

			resultString += decodedEntityMap.symbol;
			pos = indexStart + decodedEntityMap.length;
		}
		else
		{
			break;
		}
	}
	return resultString;
}

void HtmlDecode(std::istream& input, std::ostream& output)
{
	std::string text;
	while (!input.eof())
	{
		std::getline(input, text);
		output << HtmlDecodeText(text) << std::endl;
	}
}

int main()
{
	HtmlDecode(std::cin, std::cout);
	return 0;
}
