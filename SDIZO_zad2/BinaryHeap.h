#pragma once
#include <string>
#include "Structures.h"

class BinaryHeap
{
private:

	size_t size;

	Edge** tab;

	size_t parentIndex(int index);

	size_t childLeftIndex(int index);

	size_t childRightIndex(int index);
	
	std::string cr, cl, cp;
public:
	void load(std::string name);

	void fixDown(int index);

	void fixUp(int index);

	void push(int weight, int edgeTo,int edgeFrom);

	void push(Edge* edge);

	void pop(int number, int edgeTo,int edgeFrom);

	void pop(Edge* edge);

	void popFront();

	void add(int weight, int edgeTo);

	Edge* returnEdge(int index);

	Edge* returnEdgeTo(int edgeTo);

	Edge* returnEdgeFrom(int edgeFrom);

	bool search(int number);

	bool isEmpty();

	void display(std::string sp, std::string sn, size_t i);

	void displayTable();

	void floydFix();

	BinaryHeap(size_t size);

	~BinaryHeap();
};


