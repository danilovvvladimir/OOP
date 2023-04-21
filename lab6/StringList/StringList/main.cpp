#include "CStringList.h"
#include <iostream>

// [X] CStringListNode: ��������� ���� �� ��������, � �� �� ����� ������.
// [X] CStringListNode: ������� ���� ����������.

// [X] ��� �������� ����� ���������� �� ������������� �� std::iterator.
// [X] �������� �������������� �� �������� ��������� � �����������.

// [X] ������������� ������ ������ � ����� ���������� ������ ��� ������������������.
// [X] �������� noexcept �� ������, ������� �� ���������� ����������.

// [X] ��������� ���������� �����������: move-out ������ ������ �������� � �������� ���������.

int main()
{

	CStringList lst1;
	lst1.PushBack("hello");
	lst1.PushBack("world");

	std::cout << "lst1:" << std::endl;
	for (auto el : lst1)
	{
		std::cout << el<< std::endl;
	}
	std::cout << std::endl;

	CStringList lst2(std::move(lst1));
	lst1.PushBack("NOOT HELLO");
	lst1.PushBack("NOOT WORLD");

	std::cout << "lst1:" << std::endl;
	for (auto el : lst1)
	{
		std::cout << el << std::endl;
	}
	std::cout << std::endl;

	std::cout << "lst2:" << std::endl;
	for (auto el : lst2)
	{
		std::cout << el << std::endl;
	}
	std::cout << std::endl;


	return 0;
}