#pragma once

#include "CStringNode.h"

class CStringList
{
public:
	// ==> Constructors & destructor <==
	CStringList();
	CStringList(const CStringList& other);
	//CStringList(CStringList&& other) noexcept;

	~CStringList() noexcept;

	// ==> Operators <==
	//CStringList& operator=(const CStringList& other);
	//CStringList& operator=(CStringList&& other) noexcept;

	// ==> Methods <==
	void PushBack(const std::string& data);
	void PushFront(const std::string& data);

	//CStringList& PopBack();
	//CStringList& PopFront();

	size_t GetSize() const;
	bool IsEmpty() const;

	void Clear();

	// ==> Iterators <==

private:
	CStringNode* m_head;
	CStringNode* m_tail;
	size_t m_size;
};
