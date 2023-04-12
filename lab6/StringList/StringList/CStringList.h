#pragma once

#include <algorithm>

#include "CStringListNode.h"
#include "CStringListIterator.h"
#include "CStringListConstIterator.h"

class CStringList
{
public:
	using Iterator = CStringListIterator;
	using ConstIterator = CStringListConstIterator;
	// ==> Constructors & destructor <==
	CStringList();
	CStringList(const CStringList& other);
	CStringList(CStringList&& other) noexcept;

	~CStringList() noexcept;

	// ==> Operators <==
	CStringList& operator=(const CStringList& other);
	CStringList& operator=(CStringList&& other) noexcept;

	// ==> Methods <==
	void PushBack(const std::string& data);
	void PushFront(const std::string& data);
	Iterator Insert(const CStringListIterator& position, const std::string& data);

	size_t GetSize() const;
	bool IsEmpty() const;

	void Clear();

	// ==> Iterators <==


	Iterator begin() const;
	Iterator end() const;
	std::reverse_iterator<CStringListIterator> rbegin() const;
	std::reverse_iterator<CStringListIterator> rend() const;

	ConstIterator cbegin() const;
	ConstIterator cend() const;
	std::reverse_iterator<CStringListConstIterator> crbegin() const;
	std::reverse_iterator<CStringListConstIterator> crend() const;

private:
	CStringListNode* m_head;
	CStringListNode* m_tail;
	size_t m_size;
};
