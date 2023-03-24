#pragma once

#include <string>

constexpr char STRING_END_SYMBOL = '\0';

class CMyString
{
public:
	// ===> Constructors & destructor <===

	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	CMyString(const char* pString);

	// �����������, ���������������� ������ ������� ��
	// ����������� ������� �������� �����
	CMyString(const char* pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������
	CMyString(CMyString&& other);

	// �����������, ���������������� ������ ������� ��
	// ������ ����������� ���������� C++
	CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ===> Methods <===

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength() const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������
	const char* GetStringData() const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	// ===> Operators <===
	CMyString& operator=(CMyString const& other);
	CMyString& operator+=(CMyString const& other);
	friend std::istream& operator>>(std::istream& stream, CMyString& myString);

private:
	char* m_data;
	size_t m_length;
};
CMyString const operator+(CMyString const& myString1, CMyString const& myString2);

std::ostream& operator<<(std::ostream& stream, CMyString const& myString);
std::istream& operator>>(std::istream& stream, CMyString& myString);