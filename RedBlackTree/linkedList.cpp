// a stripped down version of linked list task from the beginning of the second semester

#include <iostream>
#include "linkedList.h"

namespace data_structures {
	template<typename T>
	 CircularDoubleLinkedList<T>::CircularDoubleLinkedList() {
		CircularDoubleLinkedList<T>::Node head = nullptr;
	}
	 
	 template<typename T>
	 CircularDoubleLinkedList<T>::~CircularDoubleLinkedList() {
		clear();
	}
	
	 template<typename T>
	 void CircularDoubleLinkedList<T>::insert(T value, unsigned long int pos ) {
		 CircularDoubleLinkedList<T>::Node* buf = new CircularDoubleLinkedList<T>::Node;
		buf->data = value;

		// if inserting in a zero length array, than we need to create a first node
		if (head == nullptr) {
			buf->next = buf;
			buf->prev = buf;
			head = buf;
			return;
		}

		CircularDoubleLinkedList<T>::Node* toInsertBefore = head;
		for (long unsigned int i = 0; i < pos; i++) {
			toInsertBefore = toInsertBefore->next;
		}

		buf->next = toInsertBefore;
		buf->prev = toInsertBefore->prev;
		buf->prev->next = buf;
		buf->next->prev = buf;

		if (pos == 0) {
			head = buf;
		}

		return;
	}
	
	 template<typename T>
	 CircularDoubleLinkedList<T>::Node* CircularDoubleLinkedList<T>::get(long unsigned int pos) {
		 Node* toGet = head;
		 for (long unsigned int i = 0; i < pos; i++) {
			 toGet = toGet->next;
		 }
		 return toGet;
	 }
	
	template<typename T>
	T& CircularDoubleLinkedList<T>::operator[](long unsigned int pos) {
		return  CircularDoubleLinkedList<T>::get(pos)->data;
	}
	
	template<typename T>
	void CircularDoubleLinkedList<T>::put(T val) {
		//insert and sort from low to high
		CircularDoubleLinkedList<T>::Node* buf = new CircularDoubleLinkedList<T>::Node;
		buf->data = val;
		if ((head == nullptr) || (head->data > val)) {
			insert(val, 0);
			return;
		}


		CircularDoubleLinkedList<T>::Node* curr = head;
		do {
			curr = curr->next;
		} while ((curr->data < val) && (curr != head));

		buf->next = curr;
		buf->prev = curr->prev;
		buf->prev->next = buf;
		buf->next->prev = buf;

		if (buf == head) {
			head = buf;
		}
		return;
	}
	
	template<typename T>
	void CircularDoubleLinkedList<T>::show(bool small ) {
		if (head == nullptr) {
			std::cout << "empty list" << std::endl;
			return;
		}
		if (small) {
			Node* last = head;
			std::cout << "{";
			do {
				std::cout << last->data << ", ";
				last = last->next;
			} while (last != head);
			std::cout << "}\n";
			return;
		}
		std::cout << "DISPLAYING...B->E" << std::endl;
		CircularDoubleLinkedList<T>::Node* last = head;
		int i = 0;
		do {
			std::cout << "item  " << ++i << " data:" << last->data << std::endl;
			last = last->next;
		} while (last != head);
		std::cout << "DISPLAYING...E->B" << std::endl;
		i = 0;

		do {
			std::cout << "item  " << (--i) << " data:" << last->data << std::endl;
			last = last->prev;
		} while (last != head);
		std::cout << "DISPLAYING... done" << std::endl;
	}
	
	template<typename T>
	unsigned long int CircularDoubleLinkedList<T>::pop(unsigned int pos) {
		if (head == nullptr) {
			return 0;
		}

		CircularDoubleLinkedList<T>::Node* toRemove = head;

		if ((pos == 0) && (head != head->next)) {
			head = toRemove->next;
		}
		else if (head == head->next)
		{
			delete head;
			head = nullptr;
			return 0;
		}
		//if node is closer to the beginning
		for (long unsigned int i = 0; i < pos; i++) {
			toRemove = toRemove->next;
		}

		toRemove->next->prev = toRemove->prev;
		toRemove->prev->next = toRemove->next;
		delete toRemove;
		toRemove = nullptr;
		return 1;
	}
	
	template<typename T>
	void CircularDoubleLinkedList<T>::clear() {
		while (head != nullptr) {
			CircularDoubleLinkedList<T>::pop(0);
		}
	}

	template<typename T>
	unsigned long int CircularDoubleLinkedList<T>::remove(T val) {
		//returns count of removed nodes
		unsigned long int remNodesCount = 0;
		CircularDoubleLinkedList<T>::Node* current = head;
		bool contFlag = false;
		if (head == nullptr) {
			return 0;
		}
		do {
			this->show();

			if (current->data == val) {
				CircularDoubleLinkedList<T>::Node* buf = current;
				current->prev->next = current->next;
				current->next->prev = current->prev;
				current = current->next;
				if (buf == head) {
					//if start pointer is deleted
					head = current;

				}
				if (buf->next == buf) {
					head = nullptr;
				}
				delete buf;
				buf = nullptr;
				remNodesCount++;
				contFlag = true;
				continue;
			}
			contFlag = false;
			current = current->next;

		} while ((head != nullptr) && ((current != head) || contFlag));

		return remNodesCount;
	}
	
	template<typename T>
	unsigned long int CircularDoubleLinkedList<T>::find(T val) {
		//returns count of found nodes
		unsigned long int remNodesCount = 0;
		CircularDoubleLinkedList<T>::Node* current = head;

		if (head == nullptr) {
			return 0;
		}
		do {

			if (current->data == val) {
				CircularDoubleLinkedList<T>::Node* buf = current;
				current->prev->next = current->next;
				current->next->prev = current->prev;
				current = current->next;
				remNodesCount++;
			}
			current = current->next;

		} while ((head != nullptr) && (current != head));

		return remNodesCount;
	}
}