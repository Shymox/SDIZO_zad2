#pragma once
#include <string>
#include "Structures.h"

struct ListElem
{
	Node *node;
	ListElem*prev, *next;
};
class List
{
private:
	int size;
	ListElem* head, * tail;
	void popElem(ListElem* elem);

public:
	void random(int size);

	void load(std::string name);

	void pushFront(Node* node);

	void pushBack(Node* node);

	void push(Node* node, size_t index);

	void popFront();

	void popBack();

	void pop(int index);

	void popNumber(Node* number);

	bool search(Node* number);

	bool search(int value,int nodeTo);

	Node* makeNode(int nodeTo, int value);

	bool isEmpty();

	Node* returnFNode();

	Node* returnNode(int i);

	ListElem* returnHead();

	void display();

	void display2();

	void erase();

	List();

	~List();

};

