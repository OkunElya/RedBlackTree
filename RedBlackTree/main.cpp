#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <random>
#include "linkedList.h"
#include "redBlackTree.h"

int main()
{
    std::random_device rd;
    std::mt19937 g(rd());
    data_structures::CircularDoubleLinkedList<int> list();
    data_structures::RedBlackTree tree;
   
    struct data_structures::dataStruct testStruct;
    int added[1200];
    for (int i = 0; i < 1200; i++) {
        added[i] = i;
    }
    std::shuffle(std::begin(added), std::end(added), g);
	for (int i = 0; i < 12; i++) {
		testStruct.number = added[i];
		tree.insert(testStruct);
	}

    tree.print();

    
}
