#pragma once
// red black tree class with insert, find ,delete functions

#include <iostream>

#ifndef RED_BLACK_TREE_CLASS_H
#define RED_BLACK_TREE_CLASS_H

namespace data_structures {
	enum Color { red, black };

	struct dataStruct {//in this case struct stores phoneNumber
		unsigned int number;
		int countryCode;
		inline bool operator==(const dataStruct& other) const;
		inline bool operator>(const dataStruct& other) const;
		inline bool operator<=(const dataStruct& other) const;
		inline bool operator<(const dataStruct& other) const;
		inline bool operator>=(const dataStruct& other) const;

	};

	class RedBlackTree {
	private:

		struct node {
			struct node* left = nullptr;
			struct node* right = nullptr;
			struct node* parent = nullptr;
			struct dataStruct data;
			enum Color color = red;
			//some 'safe' to use functions
			node* gran(); // Returns the grandparent of the node
			node* brother(); // Returns the sibling of the node
			node* uncle(); // Returns the uncle of the node
		};
		struct node* root = nullptr;



		Color color(node* node_); // Returns the color of the node

		void rotateLeft(node* toRot); // Performs a left rotation on the given node

		void rotateRight(node* toRot); // Performs a right rotation on the given node

		void print(node* current, std::string prefix = "", bool isLeft = false, int level = 0); // Prints the tree in a readable format

		void deletionBalance(node* temp); // Balances the tree after a node deletion

	public:
		void insert(dataStruct item); // Inserts a new node with the given data

		bool find(dataStruct value); // Finds a node with the given data

		bool pop(dataStruct value); // Deletes a node with the given data

		void print(); // Prints the tree in a readable format

		bool isEmpty(); // Checks if the tree is empty
	};
}
#endif // !RED_BLACK_TREE_CLASS