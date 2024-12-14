// a stripped down version of linked list task from the begining of the sencond semester

#include <iostream>
template <typename T>
class CircularDoubleLinkedList {
	struct Node {
		Node* prev = nullptr;
		Node* next = nullptr;
		T data = 0;
	};
public:
	CircularDoubleLinkedList() {
		head = nullptr;
	}

	~CircularDoubleLinkedList() {
		clear();
	}

	void insert(T value, unsigned long int pos = 0) {
		Node* buf = new Node;
		buf->data = value;

		// if inserting in a zero length array, than we need to create a first node
		if (head == nullptr) {
			buf->next = buf;
			buf->prev = buf;
			head = buf;
			return;
		}

		Node* toInsertBefore = head;
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

	Node* get(long unsigned int pos) {
		Node* toGet = head;
		for (long unsigned int i = 0; i < pos; i++) {
			toGet = toGet->next;
		}
		return toGet;
	}

	T& operator[](long unsigned int pos) {
		return get(pos)->data;
	}

	void put(T val) {
		//insert and sort from low to high
		Node* buf = new Node;
		buf->data = val;
		if ((head == nullptr) || (head->data > val)) {
			insert(val, 0);
			return;
		}


		Node* curr = head;
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

	void show(bool small = true) {
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
		Node* last = head;
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

	unsigned long int pop(unsigned int pos) {
		if (head == nullptr) {
			return 0;
		}

		Node* toRemove = head;

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

	void clear() {
		while (head != nullptr) {
			pop(0);
		}
	}

	unsigned long int remove(T val) {
		//returns count of removed nodes
		unsigned long int remNodesCount = 0;
		Node* current = head;
		bool contFlag = false;
		if (head == nullptr) {
			return 0;
		}
		do {
			this->show();

			if (current->data == val) {
				Node* buf = current;
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

	unsigned long int find(T val) {
		//returns count of found nodes
		unsigned long int remNodesCount = 0;
		Node* current = head;

		if (head == nullptr) {
			return 0;
		}
		do {

			if (current->data == val) {
				Node* buf = current;
				current->prev->next = current->next;
				current->next->prev = current->prev;
				current = current->next;
				remNodesCount++;
			}
			current = current->next;

		} while ((head != nullptr) && (current != head));

		return remNodesCount;
	}

protected:
	Node* head = nullptr;
};

