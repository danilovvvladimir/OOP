#include "CStringList.h"
#include <iostream>

// [X] CStringListNode: принимать дату по значению, а не по конст ссылке.
// [X] CStringListNode: сделать ноду структурой.

// [X] При создании своих итераторов не наследоваться от std::iterator.
// [X] Добавить преобразование из обычного итератора в константный.

// [X] Ликвидировать утечку памяти с двумя начальными нодами при деструктурировании.
// [X] Добавить noexcept на методы, которые не генерируют исключения.

// [X] Исправить констуктор перемещения: move-out объект должен остаться в валидном состоянии.

int main()
{

	//CStringList lst1;
	//lst1.PushBack("hello");
	//lst1.PushBack("world");

	//std::cout << "lst1:" << std::endl;
	//for (auto el : lst1)
	//{
	//	std::cout << el<< std::endl;
	//}
	//std::cout << std::endl;

	//CStringList lst2(std::move(lst1));
	//lst1.PushBack("NOOT HELLO");
	//lst1.PushBack("NOOT WORLD");

	//std::cout << "lst1:" << std::endl;
	//for (auto el : lst1)
	//{
	//	std::cout << el << std::endl;
	//}
	//std::cout << std::endl;

	//std::cout << "lst2:" << std::endl;
	//for (auto el : lst2)
	//{
	//	std::cout << el << std::endl;
	//}
	//std::cout << std::endl;

	///////////////////////////////////////
	//	list.PushBack("abc");
	//	list.Clear();
	//
	//	list.Erase(list.begin());
	//	list.PushBack("def");
	//	list.Clear();
	//
	//	REQUIRE(list.IsEmpty());

	CStringList list;
	list.PushBack("123");
	list.Clear();
	list.Erase(list.begin());


	for (auto el : list)
	{
		std::cout << el << std::endl;
	}

	return 0;
}