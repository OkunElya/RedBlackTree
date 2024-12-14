
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
        struct node* left;
        struct node* right;
        struct node* parent;
        struct dataStruct data;
        enum Color;

    };

    struct node* parent=nullptr;

    bool find(dataStruct value) {
        struct node* temp = parent;
        if (!temp)
            return false;//nullptrCheck
        while (temp) {
            if (value > temp->data) {
                if (value == temp->data)
                    return true;
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
    }
};

int main()
{
    RedBlackTree tree;
}
