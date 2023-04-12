#pragma once
#include "CStringListNode.h"
#include <iterator>

class CStringListIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = std::string;
	using pointer = std::string*;
	using reference = std::string&;

	CStringListIterator();
	CStringListIterator(CStringListNode* node);

	CStringListIterator operator++(int);
	CStringListIterator operator--(int);
	CStringListIterator& operator++();
	CStringListIterator& operator--();

	bool operator!=(const CStringListIterator& other) const;
	bool operator==(const CStringListIterator& other) const;

	reference operator*() const;
	pointer operator->() const;

private:
	friend class CStringList;

	CStringListNode* m_ptr;
};
