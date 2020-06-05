
#include "MatrixList.h"
#include <iostream>

MST* MatrixList::primm()
{
	if (this->tab == nullptr) return 0;
	MST* mst = new MST(this->size - 1);
	BinaryHeap* heap = new BinaryHeap(this->size);

	for (size_t i = 0;i < size;i++)
	{
		heap->push(INT_MAX, i, 0);
	}
	int j = 0;
	while (!heap->isEmpty())
	{
		Edge* u = heap->returnEdge(0);
		heap->popFront();
		int i = 0;
		while(this->tab[u->edgeTo]->returnNode(i))
		{
			if (heap->search(this->tab[u->edgeTo]->returnNode(i)->nodeTo) && this->tab[u->edgeTo]->returnNode(i)->value < heap->returnEdgeFrom(this->tab[u->edgeTo]->returnNode(i)->nodeTo)->weight)
			{
				heap->returnEdgeFrom(this->tab[u->edgeTo]->returnNode(i)->nodeTo)->weight = this->tab[u->edgeTo]->returnNode(i)->value;
				heap->returnEdgeFrom(this->tab[u->edgeTo]->returnNode(i)->nodeTo)->edgeFrom = u->edgeTo;
				mst->edges[j]->edgeFrom = u->edgeTo;
				mst->edges[j]->edgeTo = this->tab[u->edgeTo]->returnNode(i)->nodeTo;
				mst->edges[j]->weight = this->tab[u->edgeTo]->returnNode(i)->value;
			}
			i++;
		}
		heap->floydFix();
		j++;
		delete u;
	}
	for (int i = 0;i < this->size - 1;i++)
	{
		mst->value += mst->edges[i]->weight;
	}
	delete heap;
	return mst;
}

MST* MatrixList::kruskal()
{
	if (this->tab == nullptr) return 0;
	MST* mst = new MST(this->size - 1);
	Disjoint* djoint = new Disjoint(this->size);
	BinaryHeap* heap = new BinaryHeap(this->number);
	for (size_t i = 0;i < this->size;i++)
	{
		ListElem* temp = this->tab[i]->returnHead();
		
		while(temp!=nullptr)
		{
			if (temp->node->nodeTo>i)
			{
				heap->push(temp->node->value, temp->node->nodeTo, i);
			}
				temp = temp->next;
		}
	}
	int i = 0;
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
		delete heap->returnEdge(0);
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

Pth* MatrixList::dijkstra()
{
	if (this->tab == nullptr) return 0;
	Pth* pth = new Pth(this->size);
	BinaryHeap* heap = new BinaryHeap(this->size);

	for (int i = 0;i < this->size;i++)
	{
		heap->push(INT_MAX, i, 0);
	}
	heap->returnEdgeTo(this->start)->weight = 0;
	heap->floydFix();
	while (!heap->isEmpty())
	{
		Edge* u = heap->returnEdge(0);
		pth->nodes[u->edgeTo]->value = u->weight;
		pth->nodes[u->edgeTo]->nodeTo = u->edgeFrom;
		heap->popFront();
		ListElem* temp = this->tab[u->edgeTo]->returnHead();
		while (temp != nullptr)
		{
			if (heap->returnEdgeTo(temp->node->nodeTo)->weight > u->weight + temp->node->value)
			{
				heap->returnEdgeTo(temp->node->nodeTo)->weight = u->weight + temp->node->value;
				heap->returnEdgeTo(temp->node->nodeTo)->edgeFrom = u->edgeTo;
				heap->floydFix();
			}
			temp = temp->next;
		}
		delete u;
	}
	delete heap;
	return pth;
}

Pth* MatrixList::bellmanFord()
{
	if (this->tab == nullptr) return 0;
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
			ListElem* temp = this->tab[j]->returnHead();
			while(temp!=nullptr)
			{
				if (pth->nodes[j]->value!=INT_MAX && pth->nodes[temp->node->nodeTo]->value > pth->nodes[j]->value + temp->node->value)
				{
					pth->nodes[temp->node->nodeTo]->value = pth->nodes[j]->value + temp->node->value;
					pth->nodes[temp->node->nodeTo]->nodeTo = j;
				}
				temp = temp->next;
			}
		}
	}
	for (int j = 0;j < this->size;j++)
	{
		ListElem* temp = this->tab[j]->returnHead();
		while (temp != nullptr)
		{
			if (pth->nodes[j]->value != INT_MAX && pth->nodes[temp->node->nodeTo]->value > pth->nodes[j]->value + temp->node->value)
			{
				pth->cycle = true;
				return pth;
			}
			temp = temp->next;
		}
	}
	return pth;
}

void MatrixList::push(int value,size_t start, size_t end)
{
	this->tab[start]->pushBack(this->tab[start]->makeNode(end, value));
	this->number++;
}

void MatrixList::init(size_t size)
{
	this->erase();
	this->size=size;
	this->tab = new List * [this->size];
	for (int i = 0;i < this->size;i++)
	{
		this->tab[i] = new List();
	}
}

void MatrixList::erase()
{
	if (tab != nullptr)
	{
		for (size_t i = 0;i < this->size;i++)
		{
			delete this->tab[i];
		}
		delete[] tab;
		this->tab = nullptr;
		this->size = 0;
		this->number = 0;
		this->start = 0;
	}
}

void MatrixList::display()
{
	for (size_t i=0;i < this->size;i++)
	{
		std::cout << i << ": ";
		this->tab[i]->display();
		std::cout << "\n";
	}
}

MatrixList::MatrixList()
{
	this->tab = nullptr;
	this->size = 0;
	this->number = 0;
	this->start = 0;
}

MatrixList::~MatrixList()
{
	this->erase();
}
