#pragma once
// a stripped down version of linked list task from the beginning of the second semester

#include <iostream>
#ifndef CDLL_CLASS_H // include guard
#define CDLL_CLASS_H

template <typename T>
class CircularDoubleLinkedList {
	struct Node ;
public:
	CircularDoubleLinkedList();
	~CircularDoubleLinkedList();
	void insert(T value, unsigned long int pos = 0);//inserts by position
	Node* get(long unsigned int pos);//returns node of the selected position
	double& operator[](long unsigned int pos);//returns data of the node on the selected position
	void put(T val);//sorted insert
	void show(bool small = true);//displays the list
	unsigned long int pop(unsigned int pos);//removes value by position
	void clear();//clears the whole list,used in destructor
	unsigned long int remove(T val);//remover by value
	unsigned long int find(T val);//searches for selected value and returns found count
protected:
	Node* head ;
};
#endif