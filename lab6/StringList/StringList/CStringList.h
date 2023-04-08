#pragma once

//#include "CStringNode.h"
#include <string>
#include <algorithm>

class CStringList
{
public:
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

	//CStringList& PopBack();
	//CStringList& PopFront();

	size_t GetSize() const;
	bool IsEmpty() const;

	void Clear();

	// ==> Iterators <==

private:
	class CStringNode
	{
	public:
		CStringNode()
			: m_data("")
			, m_next(nullptr)
			, m_prev(nullptr)
		{
		}

		CStringNode(std::string const& data)
			: m_data(data)
			, m_next(nullptr)
			, m_prev(nullptr)
		{
		}
		CStringNode* m_next;
		CStringNode* m_prev;
		std::string m_data;
	};

	CStringNode* m_head;
	CStringNode* m_tail;
	size_t m_size;
};
