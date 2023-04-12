#include "CStringListNode.h"

CStringListNode::CStringListNode()
	: m_data("")
	, m_next(nullptr)
	, m_prev(nullptr)
{
}

CStringListNode::CStringListNode(std::string const& data)
	: m_data(std::move(data))
	, m_next(nullptr)
	, m_prev(nullptr)
{
}