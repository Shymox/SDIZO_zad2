
#include "Structures.h"
#include <iostream>

void MST::display()
{
	if (this != 0)
	{
		std::cout << "Wartosc:" << this->value << '\n';
		std::cout << "Krawedzie:" << '\n';
		for (int i = 0;i < this->number;i++)
		{
			std::cout << "[" << this->edges[i]->edgeFrom << " " << this->edges[i]->edgeTo << " " << this->edges[i]->weight << "]\n";
		}
	}
	else std::cout << "Blad pusta macierz"<< '\n';
}

MST::MST(size_t size)
{
	this->number = size;
	this->value = 0;
	this->edges = new Edge * [this->number];
	for (int i = 0;i < this->number;i++)
	{
		this->edges[i] = new Edge();
	}
}

MST::~MST()
{
	this->value = 0;
	for (int i = 0;i < this->number;i++)
	{
		delete this->edges[i];
	}
	delete[] edges;
	this->number = 0;
}

void Pth::display()
{
	if (this != 0)
	{
		if(cycle) std::cout << "Wystepuje cykl ujemny" << '\n';
		std::cout << "Krawedzie:" << '\n';
	for (int i = 0;i < this->number;i++)
	{
		std::cout <<"["<< i <<" "<< this->nodes[i]->nodeTo << " " << this->nodes[i]->value <<"]"<< '\n';
	}
	}
	else std::cout << "Blad pusta lista" << '\n';
}

Pth::Pth(size_t size)
{
	this->cycle = false;
	this->number = size;
	this->nodes = new Node * [this->number];
	for (int i = 0;i < this->number;i++)
	{
		this->nodes[i] = new Node();
	}
}

Pth::~Pth()
{
	this->cycle = false;
	for (int i = 0;i < this->number;i++)
	{
		delete this->nodes[i];
	}
	delete[] nodes;
	this->number = 0;
}

void Disjoint::Union(int x, int y)
{
	int a = Find(x);
	int b = Find(y);
	node[a] = b;
}

int Disjoint::Find(int x)
{
	if (node[x] != x)
		node[x] = Find(node[x]);
		return node[x];
}

Disjoint::Disjoint(size_t size)
{
	this->number = size;
	this->node = new int[this->number];
	for (int i = 0;i < this->number;i++)
	{
		this->node[i] = i;
	}
}


Disjoint::~Disjoint()
{
	this->number = 0;
	delete[] this->node;
}
