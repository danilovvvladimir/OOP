#pragma once
#include "CStringListNode.h"
#include "CStringListIterator.h"
#include <iterator>

class CStringListConstIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = std::string;
	using pointer = std::string*;
	using reference = std::string&;

	CStringListConstIterator();
	CStringListConstIterator(CStringListNode* node);

	CStringListConstIterator operator++(int);
	CStringListConstIterator operator--(int);
	CStringListConstIterator& operator++();
	CStringListConstIterator& operator--();

	bool operator!=(const CStringListConstIterator& other) const;
	bool operator==(const CStringListConstIterator& other) const;

	reference operator*() const;
	pointer operator->() const;

private:
	friend class CStringList;

	CStringListNode* m_ptr;
};

