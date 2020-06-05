#include "Matrix.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>
#include "BinaryHeap.h"
#include "List.h"

MST *Matrix::primm()
{
	if (this->matrix == nullptr) return 0;
	MST* mst = new MST(this->size-1);
	BinaryHeap* heap = new BinaryHeap(this->size);
	for (size_t i = 0;i < size;i++)
	{
		heap->push(INT_MAX,i,0);
	}
	int j = 0;
	while (!heap->isEmpty())
	{
		Edge* u = heap->returnEdge(0);
			heap->popFront();
			
		for (int i = 0;i<this->size; i++)
		{
			if (this->matrix[i][u->edgeTo] != 0)
			{
				if (heap->search(i) && this->matrix[i][u->edgeTo] < heap->returnEdgeFrom(i)->weight)
				{
					heap->returnEdgeFrom(i)->weight = this->matrix[i][u->edgeTo];
					heap->returnEdgeFrom(i)->edgeFrom = u->edgeTo;
					mst->edges[j]->edgeFrom = u->edgeTo;
					mst->edges[j]->edgeTo = i;
					mst->edges[j]->weight = this->matrix[i][u->edgeTo];
				}
			}
		}
		heap->floydFix();
		j++;
		delete u;
	}
	for (int i = 0;i < this->size - 1;i++)
	{
		mst->value+=mst->edges[i]->weight;
	}
	delete heap;
	return mst;
}

MST *Matrix::kruskal()
{
	if (this->matrix == nullptr) return 0;
	MST* mst = new MST(this->size - 1);
	Disjoint* djoint = new Disjoint(this->size);
	BinaryHeap* heap = new BinaryHeap(this->number);
	for (size_t i = 0;i < this->size;i++)
	{
		for (size_t j = this->size - 1;j > i; j--)
			if (this->matrix[i][j])
			{
				heap->push(this->matrix[i][j], i, j);
			}
	}
		int i=0;
		while (!heap->isEmpty())
		{
			if (djoint->Find(heap->returnEdge(0)->edgeFrom) != djoint->Find(heap->returnEdge(0)->edgeTo))
			{
				djoint->Union(heap->returnEdge(0)->edgeFrom, heap->returnEdge(0)->edgeTo);
				mst->edges[i]->edgeFrom = heap->returnEdge(0)->edgeFrom;
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

Pth* Matrix::dijkstra()
{
	if (this->matrix == nullptr) return 0;
	Pth* pth = new Pth(this->size);
	BinaryHeap* heap = new BinaryHeap(this->size);

	for (int i = 0;i < this->size;i++)
	{
		heap->push(INT_MAX, i, 0);
	}
	heap->returnEdgeTo(this->start)->weight=0;
	heap->floydFix();
	while (!heap->isEmpty())
	{
		Edge* u = heap->returnEdge(0);
		pth->nodes[u->edgeTo]->value = u->weight;
		pth->nodes[u->edgeTo]->nodeTo = u->edgeFrom;
		heap->popFront();
		for (int i = 0;i < this->size;i++)
		{

			if (this->matrix[i][u->edgeTo] > 0 && heap->returnEdgeTo(i)->weight > u->weight + this->matrix[i][u->edgeTo])
			{

				heap->returnEdgeTo(i)->weight = u->weight + this->matrix[i][u->edgeTo];
				heap->returnEdgeTo(i)->edgeFrom = u->edgeTo;
				heap->floydFix();

			}
		}
		delete u;
	}
	delete heap;
	return pth;
}

Pth* Matrix::bellmanFord()
{
	if (this->matrix == nullptr) return 0;
	Pth* pth = new Pth(this->size);

	for (int i = 0;i < this->size;i++)
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
				if (this->matrix[j][k] && pth->nodes[k]->value!=INT_MAX && pth->nodes[j]->value >pth->nodes[k]->value + this->matrix[j][k])
				{
					pth->nodes[j]->value = pth->nodes[k]->value + this->matrix[j][k];
					pth->nodes[j]->nodeTo = k;
				}
			}
		}
	}
	for (int j = 0;j < this->size;j++)
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

void Matrix::push(int value,size_t start,size_t end)
{
	if (start != end)
	{
 		this->matrix[end][start] = value;
		this->number++;
	}
}

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

Matrix::Matrix()
{
	this->matrix = nullptr;
	this->size = 0;
	this->start = 0;
	this->number = 0;
}

Matrix::~Matrix()
{
	this->erase();
}
