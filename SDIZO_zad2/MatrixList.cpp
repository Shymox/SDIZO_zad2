
#include "MatrixList.h"
#include <iostream>
//funkcja obliczaj�ca algorytm primma
MST* MatrixList::primm()
{
	if (this->tab == nullptr) return 0;
	MST* mst = new MST(this->size - 1);
	BinaryHeap* heap = new BinaryHeap(this->size);

	for (size_t i = 0;i < size;i++) //uzupe�nianie kopca warto�ciami pocz�tkowymi
	{
		heap->push(INT_MAX, i, 0);
	}
	while (!heap->isEmpty())
	{
		Edge* u = heap->returnEdge(0);
		if (u->edgeTo > 0) //wpisywanie warto�ci do tablicy wynik�w
		{
			mst->edges[u->edgeTo - 1]->edgeFrom = u->edgeFrom;
			mst->edges[u->edgeTo - 1]->edgeTo = u->edgeTo;
			mst->edges[u->edgeTo - 1]->weight = u->weight;
		}
		heap->popFront();
		int i = 0;
		while(this->tab[u->edgeTo]->returnNode(i))//p�tla wykonywana dop�ki wyst�puj� kraw�dzie po��czone z wierzcho�kiem u->edge
		{
			if (heap->search(this->tab[u->edgeTo]->returnNode(i)->nodeTo) && this->tab[u->edgeTo]->returnNode(i)->value < heap->returnEdgeTo(this->tab[u->edgeTo]->returnNode(i)->nodeTo)->weight)//sprawdzanie czy dana kraw�dz jest w kopcu oraz czy spelniony jest warunek poprawy
			{
				heap->returnEdgeTo(this->tab[u->edgeTo]->returnNode(i)->nodeTo)->weight = this->tab[u->edgeTo]->returnNode(i)->value;
				heap->returnEdgeTo(this->tab[u->edgeTo]->returnNode(i)->nodeTo)->edgeFrom = u->edgeTo;
			}
			i++;
		}
		heap->floydFix();
		delete u;
	}
	for (int i = 0;i < this->size - 1;i++)//obliczanie ��czniej warto�ci kraw�dzi 
	{
		mst->value += mst->edges[i]->weight;
	}
	delete heap;
	return mst;
}
//funkcja obliczaj�ca algorytm kruskala
MST* MatrixList::kruskal()
{
	if (this->tab == nullptr) return 0;
	MST* mst = new MST(this->size - 1);
	Disjoint* djoint = new Disjoint(this->size);
	BinaryHeap* heap = new BinaryHeap(this->number);
	for (size_t i = 0;i < this->size;i++)
	{
		ListElem* temp = this->tab[i]->returnHead();
		
		while(temp!=nullptr) //wype�nianie kopca kraw�dziami grafu
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
		if (djoint->Find(heap->returnEdge(0)->edgeFrom) != djoint->Find(heap->returnEdge(0)->edgeTo))//sprawdzenie czy wybrane kraw�dzie s� w tym samym poddrzewie
		{
			djoint->Union(heap->returnEdge(0)->edgeFrom, heap->returnEdge(0)->edgeTo);//po��czenie poddrzew
			mst->edges[i]->edgeFrom = heap->returnEdge(0)->edgeFrom;//wpisanie warto�ci do tablicy wynikowej
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
//funkcja obliczaj�ca algorytm dijkstry
Pth* MatrixList::dijkstra()
{
	if (this->tab == nullptr) return 0;
	Pth* pth = new Pth(this->size);
	BinaryHeap* heap = new BinaryHeap(this->size);

	for (int i = 0;i < this->size;i++) //wpisanie wszystkich wierzcho�k�w do kopca z warto�ciami pocz�tkowymi
	{
		heap->push(INT_MAX, i, 0);
	}
	heap->returnEdgeTo(this->start)->weight = 0;//wybranie wierzcho�ka pocz�tkowego
	heap->floydFix();
	while (!heap->isEmpty())
	{
		Edge* u = heap->returnEdge(0);
		pth->nodes[u->edgeTo]->value = u->weight; //wpisanie warto�ci do tablicy wynikowej
		pth->nodes[u->edgeTo]->nodeTo = u->edgeFrom;
		heap->popFront();
		ListElem* temp = this->tab[u->edgeTo]->returnHead();
		while (temp != nullptr)
		{
			if (heap->returnEdgeTo(temp->node->nodeTo)->weight > u->weight + temp->node->value) //sprawdzenie czy wyst�puje poprawa 
			{
				heap->returnEdgeTo(temp->node->nodeTo)->weight = u->weight + temp->node->value;//relaksacja kraw�dzi
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
//funkcja obliczaj�ca algorytm BellmanaForda
Pth* MatrixList::bellmanFord()
{
	if (this->tab == nullptr) return 0;
	Pth* pth = new Pth(this->size);

	for (int i = 0;i < this->size;i++)
	{
		pth->nodes[i]->nodeTo = 0; //wpisanie pocz�tkowych warto�ci do tablicy (kt�ra jest tablic� wynikow�)
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
				if (pth->nodes[j]->value!=INT_MAX && pth->nodes[temp->node->nodeTo]->value > pth->nodes[j]->value + temp->node->value)//sprawdzenie czy wyst�puje poprawa
				{
					pth->nodes[temp->node->nodeTo]->value = pth->nodes[j]->value + temp->node->value;//relaksacja kraw�dzi
					pth->nodes[temp->node->nodeTo]->nodeTo = j;
				}
				temp = temp->next;
			}
		}
	}
	for (int j = 0;j < this->size;j++) //sprawdzenie czy nie wyst�puje cykl ujemny
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
//dodanie krawedzi do listy
void MatrixList::push(int value,size_t start, size_t end)
{
	this->tab[start]->pushBack(this->tab[start]->makeNode(end, value));
	this->number++;
}
//inicjalizacja listy s�siedztwa o podanej liczbie wierzcho�k�w
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
//wymazanie wartosci z listy s�siedztwa
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
//wyswietlenie zawartosci listy sasiedztwa 
void MatrixList::display()
{
	for (size_t i=0;i < this->size;i++)
	{
		std::cout << i << ": ";
		this->tab[i]->display();
		std::cout << "\n";
	}
}
//konstruktor MatrixList
MatrixList::MatrixList()
{
	this->tab = nullptr;
	this->size = 0;
	this->number = 0;
	this->start = 0;
}
//destruktor MatrixList
MatrixList::~MatrixList()
{
	this->erase();
}
