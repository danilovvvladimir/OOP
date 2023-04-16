#include "CStringList.h"

// Creating 2 nodes for head & tail, and make them one based on tail
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

	for (const std::string& element : other)
	{
		try
		{
			PushBack(element);
		}
		catch (const std::exception&)
		{
			Clear();
			throw;
		}
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
	m_head = nullptr;
	m_tail = nullptr;
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
		m_head->m_prev->m_next = m_tail;
		m_tail->m_prev = m_head->m_prev;

		CStringListNode* tempNode;
		while ((tempNode = m_head) != m_tail)
		{
			m_head = m_head->m_next;
			delete tempNode;
		}

		m_size = 0;
	}
}

void CStringList::PushBack(const std::string& data)
{
	Insert(end(), data);
}

void CStringList::PushFront(const std::string& data)
{
	Insert(begin(), data);
}

void CStringList::Insert(Iterator const& position, const std::string& data)
{
	CStringListNode* newNodePtr = new CStringListNode(data);
	CStringListNode* positionPtr = position.m_nodePtr;

	// binding node to list
	newNodePtr->m_next = positionPtr;
	newNodePtr->m_prev = positionPtr->m_prev;

	// binding prev & next ptrs of position to new node
	positionPtr->m_prev->m_next = newNodePtr;
	positionPtr->m_prev = newNodePtr;

	if (positionPtr == m_head)
	{
		m_head = newNodePtr;
	}

	m_size++;
}

void CStringList::Erase(Iterator const& position)
{
	if (IsEmpty())
	{
		throw std::out_of_range("List is out of range");
	}

	CStringListNode* positionPtr = position.m_nodePtr;

	if (positionPtr->m_next == nullptr || positionPtr->m_prev == nullptr)
	{
		throw std::out_of_range("Erasing past-the-end-iterator");
	}

	CStringListNode* followingPtr;
	positionPtr->m_prev->m_next = followingPtr = positionPtr->m_next;
	positionPtr->m_next->m_prev = positionPtr->m_prev;

	if (positionPtr == m_head)
	{
		m_head = m_head->m_next;
	}

	delete positionPtr;
	m_size--;
}

CStringList::Iterator CStringList::begin() const
{
	return Iterator(m_head);
}

CStringList::Iterator CStringList::end() const
{
	return Iterator(m_tail);
}

CStringList::ReverseIterator CStringList::rbegin() const
{
	return std::make_reverse_iterator(end());
}

CStringList::ReverseIterator CStringList::rend() const
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

CStringList::ReverseConstIterator CStringList::crbegin() const
{
	return std::make_reverse_iterator(cend());
}

CStringList::ReverseConstIterator CStringList::crend() const
{
	return std::make_reverse_iterator(cbegin());
}