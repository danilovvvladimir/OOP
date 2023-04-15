#include "CStringListConstIterator.h"

CStringListConstIterator::CStringListConstIterator(CStringListNode* node)
	: m_nodePtr(node)
{
}

bool CStringListConstIterator::operator!=(CStringListConstIterator const& other) const
{
	return m_nodePtr != other.m_nodePtr;
}

bool CStringListConstIterator::operator==(CStringListConstIterator const& other) const
{
	return m_nodePtr == other.m_nodePtr;
}

CStringListConstIterator::reference CStringListConstIterator::operator*() const
{
	return m_nodePtr->m_data;
}

CStringListConstIterator::pointer CStringListConstIterator::operator->() const
{
	return &m_nodePtr->m_data;
}

CStringListConstIterator& CStringListConstIterator::operator++()
{
	m_nodePtr = m_nodePtr->m_next;
	return *this;
}

CStringListConstIterator& CStringListConstIterator::operator--()
{
	m_nodePtr = m_nodePtr->m_prev;
	return *this;
}

CStringListConstIterator CStringListConstIterator::operator++(int)
{
	CStringListConstIterator tmp(*this);
	++(*this);
	return tmp;
}

CStringListConstIterator CStringListConstIterator::operator--(int)
{
	CStringListConstIterator tmp(*this);
	--(*this);
	return tmp;
}
