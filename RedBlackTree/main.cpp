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
    for (int tries = 0; tries < 1000; tries++) {
        struct data_structures::dataStruct testStruct;
        int added[1200];
        for (int i = 0; i < 1200; i++) {
            added[i] = i;
        }
        std::shuffle(std::begin(added), std::end(added), g);
		for (int i = 0; i < 1200; i++) {
			testStruct.number = added[i];
			tree.insert(testStruct);
		}

        std::cout << "\n";

        // Mix up elements in the added array
        
        std::shuffle(std::begin(added), std::end(added), g);

        for (int i = 0; i < 1200; i++) {
            testStruct.number = added[i];
            if (!tree.pop(testStruct)) {
                tree.print();
				std::cout << "Failed to pop " << testStruct.number << "\n";
            }
            if ((tries % 100 == 0) && (i == 1000)) {
                tree.print();
            }
        }
        if (!tree.isEmpty())
        {
            std::cout << "Tree is not empty\n SOMETHING IS WRONG";
        }
    }
}
