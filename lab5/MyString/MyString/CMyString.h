#pragma once

#include <string>

constexpr char STRING_END_SYMBOL = '\0';

class CMyString
{
public:
	// ===> Constructors & destructor <===

	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из
	// символьного массива заданной длины
	CMyString(const char* pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const& other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	//  реализуется совместно с перемещающим оператором присваивания
	CMyString(CMyString&& other);

	// конструктор, инициализирующий строку данными из
	// строки стандартной библиотеки C++
	CMyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// ===> Methods <===

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength() const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая
	const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// очистка строки (строка становится снова нулевой длины)
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