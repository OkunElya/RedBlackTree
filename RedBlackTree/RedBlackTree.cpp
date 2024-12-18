
#include <iostream>
#include <stdlib.h>
#include"linkedList.h"
enum Color { red, black };
struct dataStruct {//in this case struct stores phoneNumber
    unsigned int number;
    int countryCode;

    //operators for ease of use
    inline bool operator==(const dataStruct& other) const
    {
        return (this->countryCode == other.countryCode) && (this->number == other.number);
    }

    inline bool operator>(const dataStruct& other) const
    {
        return ((this->countryCode == other.countryCode) && (this->number > other.number))
            || (this->countryCode > other.countryCode);
    }

    inline bool operator<=(const dataStruct& other) const
    {
        return !this->operator>(other);
    }

    inline bool operator<(const dataStruct& other) const
    {
        return ((this->countryCode < other.countryCode) && (this->number < other.number)) ||
            (this->countryCode > other.countryCode);;
    }

    inline bool operator>=(const dataStruct& other) const
    {
        return !this->operator>(other);
    }

};

class RedBlackTree {
public:
    struct node {
        struct node* left=nullptr;
        struct node* right=nullptr;
        struct node* parent=nullptr;
        struct dataStruct data;
        enum Color color=red;
		//some 'safe' to use functions
        node* gran() {
			if (this->parent) {
				return this->parent->parent;
			}
			return nullptr;
        }
		node* brother() {
			if (this->parent) {
				if (this == this->parent->left)
					return this->parent->right;
				else
					return this->parent->left;
			}
			return nullptr;
		}
        node* uncle() {
			if (this->parent) {
				return this->parent->brother();
			}
			return nullptr;
        }
    };

    struct node* root = nullptr;

    Color color(node* node_) {
        if (node_ == nullptr)
            return black;
        return node_->color;
    }
    
	void rotateLeft(node* toRot) {
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
    
    void rotateRight(node* toRot) {
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
    
    void print(node* current, std::string prefix = "", bool isLeft = false, int level = 0) {
        if (!current) {
            return;//recursion end
        }

        print(current->right, prefix + (isLeft ? "|   " : "    "), false, level + 1);

        std::cout << prefix;
        std::cout << (isLeft ? "`-- " : ",-- ");

        std::cout << "[" << ((current->color == red) ? "\x1b[31m" : "") << current->data.number << ((current->color == red) ? "\x1b[0m" : "") ;
        

        if (current->parent) {
            std::cout << ":" << current->parent->data.number;
        }
        else {
            std::cout << ":NPR";
        }
        std::cout << "]" << std::endl;

        print(current->left, prefix + (isLeft ? "    " : "|   "), true, level + 1);
    }
    
public:
    void insert(dataStruct item) {
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

    bool find(dataStruct value) {
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
    
};

int main()
{
    RedBlackTree tree;
    struct dataStruct  testStruct;
    testStruct.countryCode = 11;
    for (int i = 0; i < 12; i++) {
        testStruct.number = (int)(std::rand())%100;
        std::cout << "inserting " << testStruct.number << " ";
        tree.insert(testStruct);
    }

    std::cout << "\n";
    tree.print(tree.root);
}
