#pragma once

#include <string>

class CStringNode
{
public:
//private:
	CStringNode();
	CStringNode(std::string const& data);
	CStringNode* m_next;
	CStringNode* m_prev;
	std::string m_data;
};
