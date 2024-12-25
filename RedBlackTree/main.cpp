#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#include "linkedList.h"
#include "linkedList.cpp"
#include "redBlackTree.h"
#include "redBlackTree.cpp"
struct phoneNumber {//in this case struct stores phoneNumber
	unsigned int number = 0;
	unsigned long int countryCode = 0;
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

	data_structures::CircularDoubleLinkedList<int> list;//for storage of lines with repeated elements

	std::string toString() {
		return std::to_string(countryCode) + "-" + std::to_string(number)+"("+std::to_string(list.count()) + ")";
	}
};


std::ostream& operator<<(std::ostream& os, phoneNumber& pn) {
	os << pn.toString();
	return os;
}

int main()
{
	

	class taskTree : public data_structures::RedBlackTree<phoneNumber> {
	public:
		void taskInsert(phoneNumber key,unsigned long int lineNumber) {
			phoneNumber* temp= nullptr;
			temp = get(key);
			if (!temp) {
				temp=insert(key);//if there is no such key
			}
			temp->list.insert(lineNumber);//add to list of repeated line numbers
		}
		
		void taskRemove(phoneNumber key) {
			if (get(key)) {
				if (!key.list.isEmpty()) {
					key.list.remove(key.number);//remove from list of repeated line numbers
				}
				else {
					pop(key);//remove node from the tree
				}
			}
		}
	};

	taskTree tree;

	std::ifstream dataFile;
	std::string filePath;

	while (true) {//load file 
		std::cout << "Enter the file path: ";
		//std::getline(std::cin, filePath);
		std::string filePath = "C:\\Users\\OkunElya\\Desktop\\numbers.txt";//for debug purposes
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

	//read file line by line
	std::string line;
	unsigned long int lineCounter = 0;
	bool isCorrect = true;
	while (std::getline(dataFile, line))
	{
		phoneNumber key;
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

	//display tree
	tree.print();
	
	return 0;

}
