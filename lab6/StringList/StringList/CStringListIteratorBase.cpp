#include "CStringListIteratorBase.h"

bool CStringListIteratorBase::operator!=(const CStringListIteratorBase& other) const
{
	return m_ptr != other.m_ptr;
}

bool CStringListIteratorBase::operator==(const CStringListIteratorBase& other) const
{
	return m_ptr == other.m_ptr;
}

CStringListIteratorBase CStringListIteratorBase::operator++(int)
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

CStringListIteratorBase CStringListIteratorBase::operator--(int)
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

CStringListIteratorBase& CStringListIteratorBase::operator++()
{
	if (m_ptr->m_next == nullptr)
	{
		throw std::out_of_range("Unable to increment END list iterator");
	}

	m_ptr = m_ptr->m_next;

	return *this;
}

CStringListIteratorBase& CStringListIteratorBase::operator--()
{
	if (m_ptr->m_prev == nullptr)
	{
		throw std::logic_error("Unable to decrement BEGIN list iterator");
	}

	m_ptr = m_ptr->m_prev;

	return *this;
}

CStringListIteratorBase::reference CStringListIteratorBase::operator*() const
{
	return m_ptr->m_data;
}

CStringListIteratorBase::pointer CStringListIteratorBase::operator->() const
{
	return &(m_ptr->m_data);
}

CStringListIteratorBase::CStringListIteratorBase()
	: m_ptr(nullptr)
{
}

CStringListIteratorBase::CStringListIteratorBase(CStringListNode* node)
	: m_ptr(node)
{
}

CStringListIteratorBase::~CStringListIteratorBase()
{
}
