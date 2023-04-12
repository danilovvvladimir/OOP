#pragma once

#include <string>

class CStringListNode
{
public:
	CStringListNode();
	CStringListNode(std::string const& data);

	CStringListNode* m_next;
	CStringListNode* m_prev;
	std::string m_data;
};