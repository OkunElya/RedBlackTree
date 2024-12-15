
#include <iostream>
#include"linkedList.h"
enum Color { red, black };

class RedBlackTree {
 

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

	void rotateLeft(node* toRot) {
        if (!toRot || !toRot->right) {//sanity check
            std::cerr << "Rotating node that shouldn't be rotated\n";
            return;  // Cannot rotate if node is null or has no right child
        }
        //parent handling
        inline node* newParent = toRot->right;//better readability
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

        //the roataion part itself
        node* buf = newParent->left;//the one that'll be unassigned, so wee need to remember it
        newParent->left = toRot;//make rot a left child of it's right node
        
        toRot->parent = newParent;//make node of the right of the rot it's parent
        newParent = buf;
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
        inline node* newParent = toRot->left;//better readability
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

        //the roataion part itself
        node* buf = newParent->right;//the one that'll be unassigned, so wee need to remember it
        newParent->right = toRot;//make rot a left child of it's right node

        toRot->parent = newParent;//make node of the right of the rot it's parent
        newParent = buf;
        if (buf) {
            buf->parent = toRot;
        }
    }

    struct node* root=nullptr;
    void add(dataStruct item) {
        //first do simple binary tree insertion
        node* toInsert = new node;
        toInsert->data = item;


        struct node* temp = root;
        if (!root) {
            root = toInsert;
        }
        else {
            while (temp) {
                if (item > temp->data) {
                    if (!temp->left)//
                    {
                        toInsert->parent = temp;
                        temp->left = toInsert;
                        temp = toInsert;//go to the new node
                        break;
                    }
                    else
                        temp = temp->left;
                }
                else {
                    if (!temp->right)//nullptrCheck    
                    {
                        toInsert->parent = temp;
                        temp->right = toInsert;
                        temp = toInsert;//go to the new node
                        break;
                    }
                    else
                        temp = temp->right;
                }

            }
        }
		//we-re standing on a new child node and it's color is red
    
    
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
}
