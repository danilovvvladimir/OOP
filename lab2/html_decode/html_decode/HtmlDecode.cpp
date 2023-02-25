#include "HtmlDecode.h"

struct HTMLEntity
{
	char symbol;
	size_t length;
};

const std::map<std::string, char> HTML_ENTITIES_MAP = { { "&apos;", '\'' }, { "&quot;", '\"' }, { "&lt;", '<' }, { "&gt;", '>' }, { "&amp;", '&' } };
const char AMP_SYMBOL = '&';

HTMLEntity DecodeEntity(const std::string& str)
{
	for (auto htmlEntity : HTML_ENTITIES_MAP)
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
		size_t indexStart = inputText.find(AMP_SYMBOL, pos);
		resultString += inputText.substr(pos, indexStart - pos);

		if (indexStart < inputText.size())
		{
			HTMLEntity decodedEntity = DecodeEntity(inputText.substr(indexStart));

			resultString += decodedEntity.symbol;
			pos = indexStart + decodedEntity.length;
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
