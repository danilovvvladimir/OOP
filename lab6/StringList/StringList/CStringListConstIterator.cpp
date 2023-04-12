#include "CStringListConstIterator.h"

CStringListConstIterator::CStringListConstIterator()
	: m_ptr(nullptr)
{

}

CStringListConstIterator::CStringListConstIterator(CStringListNode* node)
	: m_ptr(node)
{
}

CStringListConstIterator CStringListConstIterator::operator++(int)
{
	if (m_ptr == nullptr)
	{
		throw std::logic_error("Unable to increment uninitialized iterator");
	}

	if (m_ptr->m_next == nullptr)
	{
		throw std::out_of_range("Unable to increment END list iterator");
	}

	CStringListNode* tempPtr = m_ptr;
	m_ptr = m_ptr->m_next;

	return tempPtr;
}

CStringListConstIterator CStringListConstIterator::operator--(int)
{
	if (m_ptr == nullptr)
	{
		throw std::logic_error("Unable to decrement uninitialized iterator");
	}

	if (m_ptr->m_prev == nullptr)
	{
		throw std::out_of_range("Unable to decrement BEGIN list iterator");
	}

	CStringListNode* tempPtr = m_ptr;
	m_ptr = m_ptr->m_prev;

	return tempPtr;
}

CStringListConstIterator& CStringListConstIterator::operator++()
{
	if (m_ptr->m_next == nullptr)
	{
		throw std::out_of_range("Unable to increment END list iterator");
	}

	m_ptr = m_ptr->m_next;

	return *this;
}

CStringListConstIterator& CStringListConstIterator::operator--()
{
	if (m_ptr->m_prev == nullptr)
	{
		throw std::logic_error("Unable to decrement BEGIN list iterator");
	}

	m_ptr = m_ptr->m_prev;

	return *this;
}

bool CStringListConstIterator::operator!=(const CStringListConstIterator& other) const
{
	return m_ptr != other.m_ptr;
}

bool CStringListConstIterator::operator==(const CStringListConstIterator& other) const
{
	return m_ptr == other.m_ptr;
}

CStringListConstIterator::reference CStringListConstIterator::operator*() const
{
	return m_ptr->m_data;
}

CStringListConstIterator::pointer CStringListConstIterator::operator->() const
{
	return &(m_ptr->m_data);
}
