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
	try
	{
		CStringNode* temp = other.m_head;

		while (temp != nullptr)
		{
			PushBack(temp->m_data);
			temp = temp->m_next;
		}
	}
	catch (const std::exception&)
	{
		Clear();
		throw;
	}
}

CStringList::CStringList(CStringList&& other) noexcept
	: m_head(other.m_head)
	, m_tail(other.m_tail)
	, m_size(other.GetSize())
{
	other.m_head = nullptr;
	other.m_tail = nullptr;
	other.m_size = 0;
}

CStringList::~CStringList() noexcept
{
	Clear();
}

CStringList& CStringList::operator=(const CStringList& other)
{
	if (std::addressof(other) != this)
	{
		Clear();

		CStringList tmpCopy(other);
		std::swap(m_head, tmpCopy.m_head);
		std::swap(m_tail, tmpCopy.m_tail);
		std::swap(m_size, tmpCopy.m_size);
	}

	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
	if (std::addressof(other) != this)
	{
		std::swap(m_head, other.m_head);
		std::swap(m_tail, other.m_tail);
		std::swap(m_size, other.m_size);
	}

	return *this;
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
