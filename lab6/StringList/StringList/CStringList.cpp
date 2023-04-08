#include "CStringList.h"

CStringList::CStringList()
	: m_size(0)
	, m_head(nullptr)
	, m_tail(nullptr)
{
}

CStringList::CStringList(const CStringList& other)
	: CStringList()
{
	CStringNode* temp = other.m_head;

	while (temp != nullptr)
	{
		PushBack(temp->m_data);
		temp = temp->m_next;
	}
}

CStringList::~CStringList() noexcept
{
	Clear();
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

void CStringList::Clear()
{
	if (!IsEmpty())
	{
		CStringNode* tempNode;
		while ((tempNode = m_head) != nullptr)
		{
			m_head = m_head->m_next;
			delete tempNode;
		}
		m_size = 0;
	}
}

void CStringList::PushFront(const std::string& data)
{
	CStringNode* newNode = new CStringNode(data);
	newNode->m_next = m_head;

	if (m_head != nullptr)
	{
		m_head->m_prev = newNode;
	}

	if (m_size == 0)
	{
		m_head = m_tail = newNode;
	}
	else
	{
		m_head = newNode;
	}

	m_size++;
}

void CStringList::PushBack(const std::string& data)
{
	CStringNode* newNode = new CStringNode(data);
	newNode->m_prev = m_tail;

	if (m_tail != nullptr)
	{
		m_tail->m_next = newNode;
	}

	if (m_size == 0)
	{
		m_head = m_tail = newNode;
	}
	else
	{
		m_tail = newNode;
	}

	m_size++;
}
