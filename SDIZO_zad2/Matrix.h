#pragma once
#include <string>
#include "Structures.h"

class Matrix
{
private:
	int** matrix;
	size_t size;
	size_t number;
	size_t start;
public:
	MST *primm();

	MST *kruskal();
	
	Pth* dijkstra();

	Pth* bellmanFord();

	void push(int value, size_t start, size_t end);

	void init(size_t size);

	void erase();

	void display();

	Matrix();

	~Matrix();

};

