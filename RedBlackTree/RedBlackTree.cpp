// red black tree class with insert, find ,delete functions

#include<iostream>
#include "redBlackTree.h"

namespace data_structures {
		inline bool dataStruct::operator==(const dataStruct& other) const
		{
			return (this->countryCode == other.countryCode) && (this->number == other.number);
		}

		inline bool dataStruct::operator>(const dataStruct& other) const
		{
			return ((this->countryCode == other.countryCode) && (this->number > other.number))
				|| (this->countryCode > other.countryCode);
		}

		inline bool dataStruct::operator<=(const dataStruct& other) const
		{
			return !this->operator>(other);
		}

		inline bool dataStruct::operator<(const dataStruct& other) const
		{
			return ((this->countryCode == other.countryCode) && (this->number < other.number)) ||
				(this->countryCode < other.countryCode);
		}

		inline bool dataStruct::operator>=(const dataStruct& other) const
		{
			return !this->operator>(other);
		}


		RedBlackTree::node* RedBlackTree::node::gran() {
			if (this->parent) {
				return this->parent->parent;
			}
			return nullptr;
		}
	
		RedBlackTree::node* RedBlackTree::node::brother() {
			if (this->parent) {
				if (this == this->parent->left)
					return this->parent->right;
				else
					return this->parent->left;
			}
			return nullptr;
		}
		
		RedBlackTree::node* RedBlackTree::node::uncle() {
			if (this->parent) {
				return this->parent->brother();
			}
			return nullptr;
		}
		
		
		Color RedBlackTree::color(node* node_) {
			if (node_ == nullptr)
				return black;
			return node_->color;
		}


		void RedBlackTree::rotateLeft(node* toRot) {
			if (!toRot || !toRot->right) {//sanity check
				std::cerr << "Rotating node that shouldn't be rotated\n";
				return;  // Cannot rotate if node is null or has no right child
			}
			//parent handling
			node* newParent = toRot->right;//better readability
			if (toRot->parent) {
				if (toRot->parent->left == toRot) {
					toRot->parent->left = newParent; //because after the left turn the right node will be tha parent of the left    
				}
				else {
					toRot->parent->right = newParent;//same as before 
				}
				newParent->parent = toRot->parent;
			}
			else {
				//rotated node is the root
				root = newParent;
				newParent->parent = nullptr;
			}

			//the rotation part itself
			node* buf = newParent->left;//the one that'll be unassigned, so we need to remember it
			newParent->left = toRot;//make rot a left child of it's right node 
			toRot->parent = newParent;//make node of the right of the rot it's parent
			toRot->right = buf;
			if (buf) {
				buf->parent = toRot;
			}
		}

		void RedBlackTree::rotateRight(node* toRot) {
			if (!toRot || !toRot->left) {//sanity check
				std::cerr << "Rotating node that shouldn't be rotated\n";
				return;  // Cannot rotate if node is null or has no right child
			}
			//parent handling
			node* newParent = toRot->left;//better readability
			if (toRot->parent) {
				if (toRot->parent->left == toRot) {
					toRot->parent->left = newParent; //because after the right turn the left node will be tha parent of the left    
				}
				else {
					toRot->parent->right = newParent;//same as before 
				}
				newParent->parent = toRot->parent;
			}
			else {
				//rotated node is the root
				root = newParent;
				newParent->parent = nullptr;
			}

			//the rotation part itself
			node* buf = newParent->right;//the one that'll be unassigned, so we need to remember it
			newParent->right = toRot;//make rot a right child of it's left node
			toRot->parent = newParent;//make node of the left of the rot it's parent
			toRot->left = buf;
			if (buf) {
				buf->parent = toRot;
			}
		}

		void RedBlackTree::print(node* current, std::string prefix , bool isLeft , int level) {
			if (!current) {
				return;//recursion end
			}

			print(current->right, prefix + (isLeft ? "|   " : "    "), false, level + 1);

			std::cout << prefix;
			std::cout << (isLeft ? "`-- " : ",-- ");

			std::cout << "[" << ((current->color == red) ? "\x1b[31m" : "") << current->data.number << ((current->color == red) ? "\x1b[0m" : "");


			if (current->parent) {
				std::cout << ":" << current->parent->data.number;
			}
			else {
				std::cout << ":NPR";
			}
			std::cout << "]" << std::endl;

			print(current->left, prefix + (isLeft ? "    " : "|   "), true, level + 1);
		}

		void RedBlackTree::deletionBalance(node* temp) {
			//case 1 , node is red == has no children
			if (color(temp) == red) {
				//return here
				if (temp->parent) {//remove parent linkage if there is parent
					if (temp->parent->left == temp) {
						temp->parent->left = nullptr;
					}
					else {
						temp->parent->right = nullptr;
					}
				}
				if (temp == root) {
					root = nullptr;//dereference root it the node is root (the last node)
				}
				delete temp;
				return;
			}
			else {//any other case is based on that we are deleting black node 
				while (color(temp) == black) {
					if (color(temp->brother()) == red) {
						if (temp->brother()) {
							temp->brother()->color = black;
						}
						if (temp->parent) {
							temp->parent->color = red;
							if (temp == temp->parent->left) {
								rotateLeft(temp->parent);
							}
							else {
								rotateRight(temp->parent);
							}
						}

					}
					if (temp->brother()) {
						if (color(temp->brother()->left) == black && color(temp->brother()->right) == black)//if both children of the brother are black
						{
							temp->brother()->color = black;
							//now go balance the parent

							return;
						}
					}

				}

			}
		}

		void RedBlackTree::insert(dataStruct item) {
			//first do simple binary tree insertion
			node* toInsert = new node;
			toInsert->data = item;

			struct node* temp = root;
			if (!root) {
				root = toInsert;
				temp = toInsert;
			}
			else {
				while (temp) {
					if (item > temp->data) {
						if (!temp->right)//
						{
							toInsert->parent = temp;
							temp->right = toInsert;
							temp = toInsert;//go to the new node
							break;
						}
						else
							temp = temp->right;
					}
					else {
						if (!temp->left)//nullptrCheck    
						{
							toInsert->parent = temp;
							temp->left = toInsert;
							temp = toInsert;//go to the new node
							break;
						}
						else
							temp = temp->left;
					}
				}
			}
			//we-re standing on a new child node and it's color is red
			while ((temp != root) && (color(temp->parent) == red)) {
				if (!temp->gran()) {
					break;//if there's no grandparent than we can't determine on which side of it is our node is based
				}
				if (temp->parent == temp->gran()->left) {
					node* uncle = temp->gran()->right;
					if (color(uncle) == red) {//case 2
						temp->parent->color = black;
						uncle->color = black;
						temp->gran()->color = red;
						temp = temp->gran();
					}
					else {
						if (temp == temp->parent->right) {//fixing change of direction before insertion (case 4)
							temp = temp->parent;
							this->rotateLeft(temp);
						}
						temp->parent->color = black;//case 3
						temp->gran()->color = red;
						this->rotateRight(temp->gran());
					}
				}
				else {
					node* uncle = temp->gran()->left;
					if (color(uncle) == red) {//case 2
						temp->parent->color = black;
						uncle->color = black;
						temp->gran()->color = red;
						temp = temp->gran();
					}
					else {
						if (temp == temp->parent->left) {//case 4 
							temp = temp->parent;
							this->rotateRight(temp);
						}
						temp->parent->color = black;//case 3
						temp->gran()->color = red;
						this->rotateLeft(temp->gran());
					}
				}
			}
			root->color = black;//case 1
		}

		bool RedBlackTree::find(dataStruct value) {
			struct node* temp = root;

			while (temp) {
				if (value > temp->data) {
					if (!temp->left)//nullptrCheck
						return false;
					temp = temp->left;
				}
				else if (value < temp->data) {
					if (!temp->right)//nullptrCheck
						return false;
					temp = temp->right;
				}
				else {
					return true;//found
				}
			}
			return false;
		}

		bool RedBlackTree::pop(dataStruct value) {
			if (!root) {
				return false;//null root protection
			}

			//find the node for deletion
			struct node* temp = root;
			while (temp) {
				if (value > temp->data) {
					if (!temp->right)//nullptrCheck
						return false;
					temp = temp->right;
				}
				else if (value < temp->data) {
					if (!temp->left)//nullptrCheck
						return false;
					temp = temp->left;
				}
				else {
					break;
				}
			}

			node* deleted = temp;
			if ((temp->left == nullptr) && (temp->right == nullptr)) {
				//no children, node can de simply removed
				//remove parent linkage
				if (temp->parent) {
					if (temp == temp->parent->left) {
						temp->parent->left = nullptr;
					}
					else {
						temp->parent->right = nullptr;
					}
					deleted = temp;
				}
				else//root moment
				{
					root = nullptr;
					return true;//no tree => no balancing after deletion
				}
			}
			else if ((temp->left != nullptr) && (temp->right != nullptr)) {
				//node has both left and right children, so the algorithm has to find lowest on the right or biggest on the left
				node* toReplace = temp->left;
				while (toReplace->right != nullptr) {
					toReplace = toReplace->right;
				}//finding biggest node on the right
				temp->data = toReplace->data;

				//here because we take the node after traveling far left, it should only have one children or less  , if any then on the left.

				if (toReplace->parent->left == toReplace) {//not sure about this if, but in case of 1 child on the right there might be no way to go to the right
					toReplace->parent->left = toReplace->left;
				}
				else {
					toReplace->parent->right = toReplace->left;
				}
				if (toReplace->left) {//if child on the left is present
					toReplace->left->parent = toReplace->parent;
					toReplace->left->color = toReplace->color;
				}
				//at this point toReplace node is unlinked
				deleted = toReplace;

			}
			else if (temp->left != nullptr) {//only left child is present
				if (temp->parent) {//not the root node
					if (temp->parent->left == temp) {
						temp->parent->left = temp->left;//temp is on the left of the parent
					}
					else {
						temp->parent->right = temp->left;//... right ...
					}

				}
				else {
					root = temp->left;//root had only one child and we removed root
				}
				temp->left->parent = temp->parent;//
				deleted = temp;
			}
			else {//only right child is present
				if (temp->parent) {//not the root node
					if (temp->parent->left == temp) {
						temp->parent->left = temp->right;//temp is on the left of the parent
					}
					else {
						temp->parent->right = temp->right;//... right ...
					}

				}
				else {
					root = temp->right;//root had only one child and we removed root
				}
				temp->right->parent = temp->parent;//
				deleted = temp;
			}

			//at this point we have the deleted node
			// NOT IMPLEMENTED YET
			//deletionBalance(deleted->parent);//the deleted node will always have the parent or else the balancing won't be done.
			return true;
		}

		void RedBlackTree::print() {
			this->print(root);//just a wrapper to make it public
		}

		bool RedBlackTree::isEmpty() {
			return (root == nullptr);
		}
}