#include <iostream>
#include <stdlib.h>
#include"linkedList.h"
#include"redBlackTree.h"

int main()
{
	data_structures::CircularDoubleLinkedList<int> list();
	data_structures::RedBlackTree tree;

	struct data_structures::dataStruct  testStruct;
	testStruct.countryCode = 11;
	std::cout << "inserting \n ";
	for (int i = 0; i < 12; i++) {
		testStruct.number = (int)(std::rand()) % 100;
		std::cout << testStruct.number << " ";
		tree.insert(testStruct);
	}
	std::cout << "\n";
	tree.print();
	while (!tree.isEmpty()) {
		std::cin >> testStruct.number;
		std::cout << "deleting " << testStruct.number << ".. ";
		std::cout << tree.pop(testStruct) << "\n";
		std::cout << "\n";
		tree.print();
	}
}
