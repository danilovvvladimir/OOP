#include "CStringListIterator.h"

CStringListIterator::CStringListIterator()
	: m_ptr(nullptr)
{
}

CStringListIterator::CStringListIterator(CStringListNode* node)
	: m_ptr(node)
{
}

CStringListIterator CStringListIterator::operator++(int)
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

CStringListIterator CStringListIterator::operator--(int)
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

CStringListIterator& CStringListIterator::operator++()
{
	if (m_ptr->m_next == nullptr)
	{
		throw std::out_of_range("Unable to increment END list iterator");
	}

	m_ptr = m_ptr->m_next;


	return *this;
}

CStringListIterator& CStringListIterator::operator--()
{
	if (m_ptr->m_prev == nullptr)
	{
		throw std::logic_error("Unable to decrement BEGIN list iterator");
	}

	m_ptr = m_ptr->m_prev;

	return *this;
}

bool CStringListIterator::operator!=(const CStringListIterator& other) const
{
	return m_ptr != other.m_ptr;
}

bool CStringListIterator::operator==(const CStringListIterator& other) const
{
	return m_ptr == other.m_ptr;
}

CStringListIterator::reference CStringListIterator::operator*() const
{
	return m_ptr->m_data;
}

CStringListIterator::pointer CStringListIterator::operator->() const
{
	return &(m_ptr->m_data);
}
