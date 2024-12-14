
#include <iostream>


class RedBlackTree {
    struct dataStruct {
        
        unsigned int number;
        int countryCode;
        bool operator==(const dataStruct& other) const
        {
            return (this->countryCode== other.countryCode)&& (this->number == other.number);
        }
    };
    struct node{
       

       
    };


};

int main()
{
    std::cout << "Just a commit to start a repo\n";
}

