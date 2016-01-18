#include <iostream>
#include "list.h"

List::List() {
	first = nullptr;
}

List::~List() {
	Node* prev = first;
	Node* curr = first;
	while (curr != nullptr) {
		prev = curr;
		delete curr;
		curr = curr->next;
	}
}

bool List::exists(int d) const {
	Node* p = first;
	while (p != nullptr) {
		if (p->value == d) {
			return true;
		}
		p = p->next;
	}
	return false;
}

int List::size() const {
	int size = 0;
	Node* p = first;
	while (p != nullptr) {
		size += 1;
		p = p->next;
	}
	return size;
}

bool List::empty() const {
	return first == nullptr;
}

void List::insertFirst(int d) {
	first = new Node(d, first);
}

void List::remove(int d, DeleteFlag df) {
	Node* prev = first;
	Node* curr = first;
	while (curr != nullptr) {
		if ((df == List::DeleteFlag::LESS    && curr->value <  d) ||
			(df == List::DeleteFlag::EQUAL   && curr->value == d) ||
			(df == List::DeleteFlag::GREATER && curr->value >  d))
		{
			if (prev == first) {
				first = first->next;
			}
			prev->next = curr->next;
			delete curr;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

void List::print() const {
	Node* p = first;
	std::cout << "List( ";
	while (p != nullptr) {
		std::cout << p->value << " ";
		p = p->next;
	}
	std::cout << ")" << std::endl;
}

