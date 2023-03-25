#include "CMyString.h"

CMyString::CMyString()
	: m_data(new char[1])
	, m_length(0)
{
	m_data[0] = STRING_END_SYMBOL;
}

CMyString::CMyString(const char* pString, size_t length)
	: m_data(new char[length + 1])
	, m_length(length)
{
	memcpy(m_data, pString, length);
	m_data[m_length] = STRING_END_SYMBOL;
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_data, other.m_length)
{
}

CMyString::CMyString(CMyString&& other)
	: m_data(other.m_data)
	, m_length(other.m_length)
{
	other.m_data = nullptr;
	other.m_length = 0;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::~CMyString()
{
	delete[] m_data;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_data;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		throw std::out_of_range("<start> index is out of string range");
	}

	if (length > m_length - start)
	{
		throw std::out_of_range("<length> is out of range");
	}

	return CMyString(&m_data[start], length);
}

void CMyString::Clear()
{
	delete[] m_data;
	m_length = 0;

	m_data = new char[1];
	m_data[0] = STRING_END_SYMBOL;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (std::addressof(other) != this)
	{
		CMyString tmpCopy(other);
		std::swap(m_data, tmpCopy.m_data);
		std::swap(m_length, tmpCopy.m_length);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (std::addressof(other) != this)
	{
		m_length = 0;
		m_data = nullptr;

		std::swap(m_data, other.m_data);
		std::swap(m_length, other.m_length);
	}

	return *this;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	size_t newCMyStringLength = m_length + other.m_length;
	char* newCMyStringData = new char[newCMyStringLength + 1];

	memcpy(newCMyStringData, m_data, m_length);
	memcpy(newCMyStringData + m_length, other.m_data, other.m_length);

	newCMyStringData[newCMyStringLength] = STRING_END_SYMBOL;

	m_data = newCMyStringData;
	m_length = newCMyStringLength;

	return *this;
}

const char & CMyString::operator[](size_t index) const
{
	if (index > m_length)
	{
		throw std::out_of_range("index is out of range");
	}

	return m_data[index];
}

char& CMyString::operator[](size_t index)
{
	if (index > m_length)
	{
		throw std::out_of_range("index is out of range");
	}
	return m_data[index];
}

CMyString const operator+(CMyString const& myString1, CMyString const& myString2)
{
	//// ask about removing const& and recreating implementation using += operator

	size_t newCMyStringLength = myString1.GetLength() + myString2.GetLength();
	char* newCMyStringData = new char[newCMyStringLength];

	memcpy(newCMyStringData, myString1.GetStringData(), myString1.GetLength());
	memcpy(newCMyStringData + myString1.GetLength(), myString2.GetStringData(), myString2.GetLength());

	newCMyStringData[newCMyStringLength] = STRING_END_SYMBOL;

	return CMyString(newCMyStringData, newCMyStringLength);
}

bool operator==(CMyString const& myString1, CMyString const& myString2)
{
	if (myString1.GetLength() != myString2.GetLength())
	{
		return false;
	}

	return (strcmp(myString1.GetStringData(), myString2.GetStringData()) == 0);
}

bool operator!=(CMyString const& myString1, CMyString const& myString2)
{
	return (strcmp(myString1.GetStringData(), myString2.GetStringData()) != 0);
}

bool operator>(CMyString const& myString1, CMyString const& myString2)
{
	return (strcmp(myString1.GetStringData(), myString2.GetStringData()) > 0);
}

bool operator>=(CMyString const& myString1, CMyString const& myString2)
{
	return (strcmp(myString1.GetStringData(), myString2.GetStringData()) >= 0);
}

bool operator<(CMyString const& myString1, CMyString const& myString2)
{
	return (strcmp(myString1.GetStringData(), myString2.GetStringData()) < 0);
}

bool operator<=(CMyString const& myString1, CMyString const& myString2)
{
	return (strcmp(myString1.GetStringData(), myString2.GetStringData()) <= 0);
}

std::ostream& operator<<(std::ostream& stream, CMyString const& myString)
{
	stream << myString.GetStringData();
	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& myString)
{
	size_t resultDataSize = 1;
	size_t resultLength = 0;
	char* resultData = new char[resultDataSize];

	char ch;

	while (stream.get(ch) && ch != ' ' && ch != '\n')
	{

		resultData[resultLength] = ch;
		resultLength++;

		if (resultLength == resultDataSize)
		{
			char* newResultData = new char[resultDataSize*2];
			memcpy(newResultData, resultData, resultDataSize);
			delete[] resultData;
			resultData = newResultData;

			resultDataSize *= 2;
		}
	}
	resultData[resultLength] = STRING_END_SYMBOL;

	delete[] myString.m_data;
	myString.m_length = resultLength;
	myString.m_data = resultData;

	return stream;
}
