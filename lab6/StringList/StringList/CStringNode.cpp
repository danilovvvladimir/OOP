#include "CStringNode.h"

CStringNode::CStringNode()
	: m_data("")
	, m_next(nullptr)
	, m_prev(nullptr)
{
}

CStringNode::CStringNode(std::string const& data)
	: m_data(data)
	, m_next(nullptr)
	, m_prev(nullptr)
{
}

