#include <iostream>
#include "linkedList.h"
#include "linkedList.cpp"
#include "redBlackTree.h"
#include "redBlackTree.cpp"

int main()
{
	data_structures::RedBlackTree<int> tree;
	int a = 1;
	
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);

    tree.print();
	return 0;
}
