#pragma once

#include <string>
#include <iostream>

struct CStringListNode
{
public:
	CStringListNode()
		: m_data("")
		, m_next(nullptr)
		, m_prev(nullptr)
	{
		//std::cout << "~CStringListNode()\n";
	}

	CStringListNode(std::string data)
		: m_data(std::move(data))
		, m_next(nullptr)
		, m_prev(nullptr)
	{
		//std::cout << "~CStringListNode(data)\n";
	}

	~CStringListNode()
	{
		//std::cout << "~CStringListNode\n";
	}

	CStringListNode* m_next;
	CStringListNode* m_prev;

	std::string m_data;
};