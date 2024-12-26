#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#include "linkedList.h"
#include "linkedList.cpp"
#include "redBlackTree.h"
#include "redBlackTree.cpp"

//struct for storing phone numbers (from the task) first field is country code, second is number
struct phoneNumber {//in this case struct stores phoneNumber
	unsigned int number = 0;
	unsigned long int countryCode = 0;
	data_structures::CircularDoubleLinkedList<int> list;//for storage of lines with repeated elements
	inline bool operator==(const phoneNumber& other) const
	{
		return (this->countryCode == other.countryCode) && (this->number == other.number);
	}

	inline bool operator>(const phoneNumber& other) const
	{
		return ((this->countryCode == other.countryCode) && (this->number > other.number))
			|| (this->countryCode > other.countryCode);
	}

	inline bool operator<=(const phoneNumber& other) const
	{
		return !this->operator>(other);
	}

	inline bool operator<(const phoneNumber& other) const
	{
		return ((this->countryCode == other.countryCode) && (this->number < other.number)) ||
			(this->countryCode < other.countryCode);
	}

	inline bool operator>=(const phoneNumber& other) const
	{
		return !this->operator>(other);
	}

	std::string toString() {
		std::string output;
		output= std::to_string(countryCode) + "-" + std::to_string(number)+"("+std::to_string(list.count()) + ") [";
		auto temp = list.head;
		do {
			output= output + std::to_string( temp->data )+", ";
			temp = temp->next;
		} while (temp != list.head);
		output = output+ "]";
		return output;
	}
};
//overload of << operator for phoneNumber to print it 
static std::ostream& operator<<(std::ostream& os, phoneNumber& pn) {
	os << pn.toString();
	return os;
}
//class for storing phone numbers in a tree
class taskTree : public data_structures::RedBlackTree<phoneNumber> {
private:
	void inOrderWalk(node* temp) {
		if (!temp)
		{
			return;
		}
		inOrderWalk(temp->left);
		std::cout << temp->data << "\n";
		inOrderWalk(temp->right);

	}
public:
	void taskInsert(phoneNumber& key, unsigned long int lineNumber) {
		phoneNumber* temp = nullptr;
		temp = get(key);
		if (!temp) {
			temp = insert(key);//if there is no such key
		}
		temp->list.insert(lineNumber);//add to list of repeated line numbers
	}

	long unsigned int taskRemove(phoneNumber& key) { //returns number of row where deleted element was
		long unsigned int output = 0;
		if (get(key)) {

			key.list.remove(key.number);//remove from list of repeated line numbers
			output = key.list[0];
			key.list.pop(0);
			if (key.list.isEmpty()) {
				pop(key);
			}//remove node from the tree

		}
		return output;
	}
	

	void inOrderWalk() {
		inOrderWalk(root);
	}
};

int main()
{
	

	taskTree tree;
	phoneNumber key;
	std::ifstream dataFile;
	std::string filePath;

	while (true) {//load file 
		std::cout << "Enter the file path: ";
		std::getline(std::cin, filePath);
		
		std::cout << "\n";
		std::cin.clear();
		//check if file exists
		dataFile.open(filePath);
		if (dataFile.is_open()) {
			break;
		}
		else {
			std::cout << "File "<<filePath<<" not found. Try again.\n";
		}
	}

	std::string line;
	unsigned long int lineCounter = 0;
	bool isCorrect = true;
	while (std::getline(dataFile, line))//read file line by line
	{		
        std::regex numberPattern(R"(\d{3}-\d{7})");
		if (std::regex_match(line,numberPattern)) {
			std::string countryCode = line.substr(0, 3);
			std::string number = line.substr(4, 7);
			key.countryCode = std::stoul(countryCode);
			key.number = std::stoul(number);
			if (isCorrect)//stop inserting if there is an error in the file
				tree.taskInsert(key,lineCounter+1);
		}
		else {
			std::cout << "Error in line " << (lineCounter+1) << ": " << line << "\n";
			isCorrect = false;
		}
		lineCounter++;
	}
	if (!isCorrect) {
		std::cout << "The file contains errors. Please correct them. every line should have a format of 123-1234567 \n";
		exit(0);
	}
	else {
		std::cout << "File loaded successfully ("<<lineCounter<<" lines)\n";
	}
	dataFile.close();
	//the tree is now loaded with data
	
	tree.print();
	tree.inOrderWalk();;
	
	return 0;
}
