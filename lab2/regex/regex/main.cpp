#include <iostream>
#include <regex>
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	return true;
}

int main()
{
	system("chcp 1251 > nul");
	std::regex regexpression("(https?|ftp)"
							 "(://)"
							 "([\\w]+\.[\\w]+\.[a-z]{2,5})"
							 "(/)"
							 "(.*)");
	std::cmatch result;
	std::string str = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";

	// to lower str
	if (std::regex_match(str.c_str(), result, regexpression))
	{
		for (int i = 0; i < result.size(); i++)
		{
			std::cout << result[i] << std::endl;
		}
	}
	else
	{
		std::cout << "No" << std::endl;
	}

	return 0;
}