#pragma once
struct Node
{
	int nodeTo;
	int value;
};
struct Edge
{
	size_t edgeFrom;
	size_t edgeTo;
	int weight;
};
struct MST
{
	Edge** edges;

	size_t number;

	int value;

	void display();

	MST(size_t size);

	~MST();
};
struct Pth
{
	bool cycle;

	Node** nodes;

	size_t number;

	void display();

	Pth(size_t size);

	~Pth();
};

struct Disjoint
{
	int* node;

	size_t number;

	void Union(int x, int y);

	int Find(int x);

	Disjoint(size_t size);

	~Disjoint();
};