
#include "Structures.h"
#include <iostream>
//funkcja wy�wietlaj�ca wynik oblicze� MST
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
//konstruktor struktury MST
MST::MST(size_t size)
{
	this->number = size;
	this->value = 0;
	this->edges = new Edge * [this->number];
	for (int i = 0;i < this->number;i++)
	{
		this->edges[i] = new Edge();  //inicjalizacja kraw�dzi
	}
}
//destruktor struktury mst
MST::~MST()
{
	this->value = 0;
	for (int i = 0;i < this->number;i++)
	{
		delete this->edges[i]; //usuwanie wszystkich zapisanych kraw�dzi
	}
	delete[] edges;
	this->number = 0;
}
//unkcja wy�wietlaj�ca wynik oblicze� algorytm�w najkr�tszej �cie�ki
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
//konstruktor struktury Pth
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
//destruktor struktury Pth
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
//funkcja ��cz�ca zbiory roz��czne
void Disjoint::Union(int x, int y)
{
	int a = Find(x);
	int b = Find(y);
	node[a] = b;
}
//funkcja zwracaj�ca do jakiego zbioru nale�y dany wierzcho�ek
int Disjoint::Find(int x)
{
	if (node[x] != x)
		node[x] = Find(node[x]);
		return node[x];
}
//konstruktor Disjoint
Disjoint::Disjoint(size_t size)
{
	this->number = size;
	this->node = new int[this->number];
	for (int i = 0;i < this->number;i++)
	{
		this->node[i] = i;
	}
}

//destruktor Disjoint
Disjoint::~Disjoint()
{
	this->number = 0;
	delete[] this->node;
}
