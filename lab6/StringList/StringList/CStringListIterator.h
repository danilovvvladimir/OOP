#pragma once

#include "CStringListNode.h"
#include <iterator>
#include <stdexcept>

class CStringListIterator : public std::iterator<std::bidirectional_iterator_tag, std::string>
{
	friend class CStringList;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = std::string;
	using pointer = std::string*;
	using reference = std::string&;

	bool operator!=(CStringListIterator const& other) const;
	bool operator==(CStringListIterator const& other) const;

	reference operator*() const;
	pointer operator->() const;

	CStringListIterator& operator++();
	CStringListIterator& operator--();

	CStringListIterator operator++(int);
	CStringListIterator operator--(int);

protected:
	CStringListIterator(CStringListNode* node);

private:
	CStringListNode* m_nodePtr;
};

