#include "Matrix.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>
#include "BinaryHeap.h"
#include "List.h"
//funkcja obliczaj�ca algorytm primma
MST *Matrix::primm()
{
	if (this->matrix == nullptr) return 0;
	MST* mst = new MST(this->size-1);
	BinaryHeap* heap = new BinaryHeap(this->size);
	heap->push(0, 0, 0);
	for (size_t i = 1;i < size;i++) //uzupe�nianie kopca warto�ciami pocz�tkowymi
	{
		heap->push(INT_MAX,i,0);
	}
	while (!heap->isEmpty())
	{
		Edge* u = heap->returnEdge(0); 
		if (u->edgeTo > 0)//wpisywanie warto�ci do tablicy wynik�w
		{
			mst->edges[u->edgeTo - 1]->edgeFrom = u->edgeFrom;
			mst->edges[u->edgeTo - 1]->edgeTo = u->edgeTo;
			mst->edges[u->edgeTo - 1]->weight = u->weight;
		}
			heap->popFront();
			
		for (int i = 0;i<this->size; i++)
		{
			if (this->matrix[i][u->edgeTo] != 0) //sprawdzanie czy dana kraw�d� istnieje
			{
				if (heap->search(i) && this->matrix[i][u->edgeTo] < heap->returnEdgeTo(i)->weight) //sprawdzanie czy dana kraw�dz jest w kopcu oraz czy spelniony jest warunek poprawy
				{
					heap->returnEdgeTo(i)->weight = this->matrix[i][u->edgeTo];
					heap->returnEdgeTo(i)->edgeFrom = u->edgeTo;
				}
			}
		}
		heap->floydFix();
		delete u;
	}
	for (int i = 0;i < this->size - 1;i++)
	{
		mst->value+=mst->edges[i]->weight; //obliczanie ��czniej warto�ci kraw�dzi 
	}
	delete heap;
	return mst;
}
//funkcja obliczaj�ca algorytm kruskala
MST *Matrix::kruskal()
{
	if (this->matrix == nullptr) return 0;
	MST* mst = new MST(this->size - 1);
	Disjoint* djoint = new Disjoint(this->size);
	BinaryHeap* heap = new BinaryHeap(this->number);
	for (size_t i = 0;i < this->size;i++)
	{
		for (size_t j = this->size - 1;j > i; j--) //wype�nianie kopca kraw�dziami grafu
			if (this->matrix[i][j])
			{
				heap->push(this->matrix[i][j], i, j);
			}
	}
		int i=0;
		while (!heap->isEmpty())
		{
			if (djoint->Find(heap->returnEdge(0)->edgeFrom) != djoint->Find(heap->returnEdge(0)->edgeTo)) //sprawdzenie czy wybrane kraw�dzie s� w tym samym poddrzewie
			{
				djoint->Union(heap->returnEdge(0)->edgeFrom, heap->returnEdge(0)->edgeTo); //po��czenie poddrzew
				mst->edges[i]->edgeFrom = heap->returnEdge(0)->edgeFrom; //wpisanie warto�ci do tablicy wynikowej
				mst->edges[i]->edgeTo = heap->returnEdge(0)->edgeTo;
				mst->edges[i]->weight = heap->returnEdge(0)->weight;
				i++;
			}
			delete  heap->returnEdge(0);
			heap->popFront();
		}
		for (int j = 0;j < i;j++)
		{
			mst->value += mst->edges[j]->weight;
		}
	delete djoint;
	delete heap;
	return mst;
}
//funkcja obliczaj�ca algorytm dijkstry
Pth* Matrix::dijkstra()
{
	if (this->matrix == nullptr) return 0;
	Pth* pth = new Pth(this->size);
	BinaryHeap* heap = new BinaryHeap(this->size);

	for (int i = 0;i < this->size;i++) //wpisanie wszystkich wierzcho�k�w do kopca z warto�ciami pocz�tkowymi
	{
		heap->push(INT_MAX, i, 0);
	}
	heap->returnEdgeTo(this->start)->weight=0; //wybranie wierzcho�ka pocz�tkowego
	heap->floydFix();
	while (!heap->isEmpty())
	{
		Edge* u = heap->returnEdge(0);
		pth->nodes[u->edgeTo]->value = u->weight; //wpisanie warto�ci do tablicy wynikowej
		pth->nodes[u->edgeTo]->nodeTo = u->edgeFrom;
		heap->popFront();
		for (int i = 0;i < this->size;i++)
		{

			if (this->matrix[i][u->edgeTo] > 0 && heap->returnEdgeTo(i)->weight > u->weight + this->matrix[i][u->edgeTo]) //sprawdzenie czy wyst�puje poprawa 
			{

				heap->returnEdgeTo(i)->weight = u->weight + this->matrix[i][u->edgeTo]; //relaksacja kraw�dzi
				heap->returnEdgeTo(i)->edgeFrom = u->edgeTo;
				heap->floydFix();

			}
		}
		delete u;
	}
	delete heap;
	return pth;
}
//funkcja obliczaj�ca algorytm BellmanaForda
Pth* Matrix::bellmanFord()
{
	if (this->matrix == nullptr) return 0;
	Pth* pth = new Pth(this->size);

	for (int i = 0;i < this->size;i++) //wpisanie pocz�tkowych warto�ci do tablicy (kt�ra jest tablic� wynikow�)
	{
		pth->nodes[i]->nodeTo = 0;
		pth->nodes[i]->value = INT_MAX;
	}
	pth->nodes[this->start]->value = 0;
	for (int i = 1;i < this->size;i++)
	{
		for (int j = 0;j < this->size;j++)
		{
			for (int k = 0;k < this->size;k++)
			{
				if (this->matrix[j][k] && pth->nodes[k]->value!=INT_MAX && pth->nodes[j]->value >pth->nodes[k]->value + this->matrix[j][k]) //sprawdzenie czy wyst�puje poprawa
				{
					pth->nodes[j]->value = pth->nodes[k]->value + this->matrix[j][k]; //relaksacja kraw�dzi
					pth->nodes[j]->nodeTo = k;
				}
			}
		}
	}
	for (int j = 0;j < this->size;j++) //sprawdzenie czy nie wyst�puje cykl ujemny
	{
		for (int k = 0;k < this->size;k++)
		{
			if (this->matrix[j][k] && pth->nodes[k]->value != INT_MAX && pth->nodes[j]->value > pth->nodes[k]->value + this->matrix[j][k])
			{
				pth->cycle = true;
				return pth;
			}
		}
	}
	return pth;
}
//dodanie krawedzi do macierz
void Matrix::push(int value,size_t start,size_t end)
{
	if (start != end)
	{
 		this->matrix[end][start] = value;
		this->number++;
	}
}
//inicjalizacja macierzy o podanej liczbie wierzcho�k�w
void Matrix::init(size_t size)
{
	this->erase();
	this->size = size;
	this->matrix = new int* [this->size];
	for (size_t i = 0;i < this->size;i++)
	{
		this->matrix[i] = new int[this->size];
		for (size_t j = 0;j < this->size;j++)
		{
			this->matrix[i][j]=0;
		}
	}
}
//wymazanie zawarto�ci macierzy
void Matrix::erase()
{
	if (this->matrix != nullptr)
	{
		for (size_t i = 0;i < this->size;i++)
		{
			delete[] this->matrix[i];
		}
		delete[] this->matrix;
	}
	this->matrix = nullptr;
	this->size = 0;
	this->start = 0;
	this->number = 0;
}
//wy�wietlenie zawarto�ci macierzy
void Matrix::display()
{
		for (size_t i = 0;i < this->size;i++)
		{
			for (size_t j = 0;j < this->size;j++)
			{
				std::cout << matrix[j][i] << " ";
			}
			std::cout << "\n";
		}
}
//konstruktor Matrix
Matrix::Matrix()
{
	this->matrix = nullptr;
	this->size = 0;
	this->start = 0;
	this->number = 0;
}
//destruktor Matrix
Matrix::~Matrix()
{
	this->erase();
}
