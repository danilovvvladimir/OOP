#pragma once

#include <string>

using NodePtr = CStringNode*;
class CStringNode
{
public:
private:
	NodePtr m_next;
	NodePtr m_prev;
	std::string m_data;
};
