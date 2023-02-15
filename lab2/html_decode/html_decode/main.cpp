#include <algorithm>
#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, char> myMap = { { "&apos;", '\'' }, { "&quot;", '\"' }, { "&lt;", '<' }, { "&gt;", '>' }, { "&amp;", '&' } };

struct HTMLEntity
{
	char symbol;
	size_t length;
};

HTMLEntity DecodeString(const string& str)
{
	for (auto mapEntity : myMap)
	{
		size_t firstSize = mapEntity.first.size();
		string temp = str.substr(0, firstSize);
		if (temp == mapEntity.first)
		{
			return { mapEntity.second, mapEntity.first.size() - 1 };
		}
	}
	return { '&', 0 };
}

int main()
{

	string inString = "&quot;Hello&quot;&quot;";
	//string inString = "&&lt;h1&gt;";

	//string inString;
	//getline(cin, inString);

	string result;

	for (size_t pos = 0; pos < inString.size(); pos++)
	{
		auto indexStart = inString.find('&', pos);
		result += inString.substr(pos, indexStart - pos);

		if (indexStart < inString.size())
		{
			HTMLEntity decodedEntityMap = DecodeString(inString.substr(indexStart));

			result += decodedEntityMap.symbol;
			pos = indexStart + decodedEntityMap.length;
		}
		else
		{
			break;
		}
	}
	cout << result << endl;

	return 0;
}
