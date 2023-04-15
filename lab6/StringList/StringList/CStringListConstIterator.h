#pragma once

#include "CStringListNode.h"
#include <iterator>

class CStringListConstIterator : public std::iterator<std::bidirectional_iterator_tag, const std::string>
{
	friend class CStringList;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = const std::string;
	using pointer = const std::string*;
	using reference = const std::string&;

	bool operator!=(CStringListConstIterator const& other) const;
	bool operator==(CStringListConstIterator const& other) const;

	reference operator*() const;
	pointer operator->() const;

	CStringListConstIterator& operator++();
	CStringListConstIterator& operator--();

	CStringListConstIterator operator++(int);
	CStringListConstIterator operator--(int);

protected:
	CStringListConstIterator(CStringListNode* node);

private:
	CStringListNode* m_nodePtr;
};
