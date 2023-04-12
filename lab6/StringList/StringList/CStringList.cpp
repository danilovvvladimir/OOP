#include "CStringList.h"

CStringList::CStringList()
	: m_size(0)
	, m_head(new CStringListNode())
	, m_tail(nullptr)
{
	try
	{
		m_tail = new CStringListNode();
	}
	catch (const std::bad_alloc&)
	{
		delete m_head;
		throw;
	}

	m_head->m_next = m_tail;
	m_tail->m_prev = m_head;
	m_head = m_tail;
}

CStringList::CStringList(const CStringList& other)
	: CStringList()
{
	try
	{
		CStringListNode* temp = other.m_head;

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
	// delete head & tail?
	delete m_head->m_prev;
	delete m_tail;
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
		Clear();

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
		CStringListNode* tempNode;
		while ((tempNode = m_head) != nullptr)
		{
			m_head = m_head->m_next;
			delete tempNode;
		}
		m_size = 0;
	}
}

CStringList::Iterator CStringList::begin() const
{
	return Iterator(m_head);
}

CStringList::Iterator CStringList::end() const
{
	return Iterator(m_tail);
}

std::reverse_iterator<CStringListIterator> CStringList::rbegin() const
{
	return std::make_reverse_iterator(end());
}

std::reverse_iterator<CStringListIterator> CStringList::rend() const
{
	return std::make_reverse_iterator(begin());
}

CStringList::ConstIterator CStringList::cbegin() const
{
	return ConstIterator(m_head);
}

CStringList::ConstIterator CStringList::cend() const
{
	return ConstIterator(m_tail);
}

std::reverse_iterator<CStringListConstIterator> CStringList::crbegin() const
{
	return std::make_reverse_iterator(cend());
}

std::reverse_iterator<CStringListConstIterator> CStringList::crend() const
{
	return std::make_reverse_iterator(cbegin());
}


void CStringList::PushFront(const std::string& data)
{
	CStringListNode* newNode = new CStringListNode(data);
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

CStringList::Iterator CStringList::Insert(const CStringListIterator& position, const std::string& data)
{
	CStringListNode* newNodePtr = new CStringListNode(data);
	CStringListNode* wherePtr = position.m_ptr;

	newNodePtr->m_next = wherePtr;
	newNodePtr->m_prev = wherePtr->m_prev;
	wherePtr->m_prev->m_next = newNodePtr;
	wherePtr->m_prev = newNodePtr;

	if (wherePtr == m_head)
	{
		m_head = newNodePtr;
	}

	++m_size;

	return Iterator(newNodePtr);
}

void CStringList::PushBack(const std::string& data)
{
	CStringListNode* newNode = new CStringListNode(data);
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
