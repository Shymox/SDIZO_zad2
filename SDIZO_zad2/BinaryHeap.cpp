#include "BinaryHeap.h"
#include <iostream>
#include <fstream>

/*
Klasa zawieraj¹ca Kopiec oraz funkcje potrzebne do jego obs³ugi
*/
//funkcja zwraca index rodzica wezla o podanym indexie
size_t BinaryHeap::parentIndex(int index)
{	
	return (index-1)/2;
}
//funkcja zwraca index lewego dziecka wezla o podanym indexie
size_t BinaryHeap::childLeftIndex(int index)
{
	return 2*index+1;
}
//funkcja zwraca index prawego dziecka wezla o podanym indexie
size_t BinaryHeap::childRightIndex(int index)
{
	return 2*index+2;
}
//funkcja pobiera kopiec z pliku
void BinaryHeap::load(std::string name)
{
	this->size = 0;
	std::fstream file;
	file.open(name, std::ios::in | std::ios::out);
	if (file.good() == true)
	{
		size_t size = 0;
		std::cout << "Uzyskano dostep do pliku!" << std::endl;
		std::string data;
		getline(file, data);
		try {
			size = static_cast<size_t>(std::stoi(data),1);
		}
		catch (std::exception)
		{
			std::cout << "B³¹d odczytu: std::exception" << '\n';
		}
		this->size = 0;
		while (!file.eof() && this->size < size)
		{
			getline(file, data);
			try
			{
				push(static_cast<int>(std::stoi(data)),1,1);
			}
			catch (std::exception)
			{
				std::cout << "Blad odczytu: std::exception" << '\n';
			}
		}
		file.close();
		if ((this->size) < size)
		{
			std::cout << "Blad odczytu: Rozmiar listy wiekszy niz ilosc danych" << '\n';
			this->size = 0;
		}
	}
	else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
}
//funkcja naprawia kopiec w dó³
void BinaryHeap::fixDown(int index)
{
	size_t largestChild = this->childLeftIndex(index);
	while (largestChild < this->size) {
		if (largestChild + 1 < this->size && this->tab[largestChild]->weight > this->tab[largestChild + 1]->weight) {
			largestChild++;
		}
		if (this->tab[index]->weight > this->tab[largestChild]->weight) {
			Edge* tmp = this->tab[index];
			this->tab[index] = this->tab[largestChild];
			this->tab[largestChild] = tmp;
			index = largestChild;
			largestChild = this->childLeftIndex(index);
		}
		else {
			largestChild = this->size;
		}

	}
}
//funkcja naprawia kopiec w górê
void BinaryHeap::fixUp(int index)
{
	while(this->tab[parentIndex(index)]->weight > this->tab[index]->weight)
	{
		Edge* temp = tab[this->parentIndex(index)];
		this->tab[this->parentIndex(index)] = this->tab[index];
		this->tab[index] = temp;
		index = this->parentIndex(index);
	}
}
//dodawanie wartoœci do kopca
void BinaryHeap::push(int weight,int edgeTo,int edgeFrom)
{
	int i = this->size;
	this->tab[this->size]->weight = weight;
	this->tab[this->size]->edgeTo = edgeTo;
	this->tab[this->size]->edgeFrom = edgeFrom;
	this->size++;
	while (i != 0 && this->tab[parentIndex(i)]->weight > this->tab[i]->weight)
	{
		Edge *temp = this->tab[this->parentIndex(i)];
		this->tab[this->parentIndex(i)] = this->tab[i];
		this->tab[i] = temp;
		i = this->parentIndex(i);
	}
}
void BinaryHeap::push(Edge* edge)
{
	int i = this->size;
	this->tab[this->size] = edge;
	this->size++;
	while (i != 0 && this->tab[parentIndex(i)]->weight > this->tab[i]->weight)
	{
		Edge* temp = this->tab[this->parentIndex(i)];
		this->tab[this->parentIndex(i)] = this->tab[i];
		this->tab[i] = temp;
		i = this->parentIndex(i);
	}
}
//usuwanie podanego numeru z kopca
void BinaryHeap::pop(int number,int edgeTo,int edgeFrom)
{
	size_t index=0;
	for (index = 0;index < this->size;index++)
	{
		if (this->tab[index]->weight == number && this->tab[index]->edgeTo == edgeTo && this->tab[index]->edgeFrom == edgeFrom)
		{
			break;
		}
		return;
	}
	this->tab[index] = this->tab[this->size - 1];
	this->size--;
	fixUp(index);
	fixDown(index);
}
void BinaryHeap::pop(Edge* edge)
{
	size_t index = 0;
	for (index = 0;index < this->size;index++)
	{
		if (this->tab[index]==edge)
		{
			break;
		}
		return;
	}
	this->tab[index] = this->tab[this->size - 1];
	this->size--;
	fixUp(index);
	fixDown(index);
}
void BinaryHeap::popFront()
{
	this->tab[0] = this->tab[this->size - 1];
	this->size--;
	this->fixDown(0);
}
//dodanie wartosci do tablicy kopca
void BinaryHeap::add(int weight,int edgeTo)
{
	this->tab[size]->weight = weight;
	this->tab[size]->edgeTo = edgeTo;
	size++;
}
Edge* BinaryHeap::returnEdge(int index)
{
	return tab[index];
}
Edge* BinaryHeap::returnEdgeTo(int edgeTo)
{
	for (int i = 0;i < this->size;i++)
	{
		if (this->tab[i]->edgeTo == edgeTo)
		{
			return tab[i];
		}
	}
	return tab[0];

}
Edge* BinaryHeap::returnEdgeFrom(int edgeFrom)
{
	for (int i = 0;i < this->size;i++)
	{
		if (this->tab[i]->edgeFrom == edgeFrom)
		{
			return tab[i];
		}
	}
	return tab[0];
}
//wyszukiwanie wartosci w kopcu (zwraca true jesli znajdzie)
bool BinaryHeap::search(int number)
{
	for (int i = 0;i < this->size;i++)
	{
		if (this->tab[i]->edgeTo == number)
		{
			return true;
		}
	}
	return false;
}
bool BinaryHeap::isEmpty()
{
	if (size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//wyswietlanie kopca
void BinaryHeap::display(std::string sp, std::string sn, size_t v)
{
		std::string s;

		if (v < this->size)
		{
			s = sp;
			if (sn == cr) s[s.length() - 2] = ' ';
			display(s + cp, cr, 2 * v + 2);

			s = s.substr(0, sp.length() - 2);

			std::cout << s << sn << this->tab[v]->weight << std::endl;

			s = sp;
			if (sn == cl) s[s.length() - 2] = ' ';
			display(s + cp, cl, 2 * v + 1);
		}
}

//wyswietlanie tablicy kopca
void BinaryHeap::displayTable()
{
	for (int i = 0;i < this->size;i++)
	{
		std::cout << this->tab[i]->weight << " " << this->tab[i]->edgeFrom << " "<< this->tab[i]->edgeTo<< "\n";
	}
}

void BinaryHeap::floydFix()
{
	for (size_t i = this->size / 2; i > 0; i--) 
	{
		this->fixDown(i - 1);
	}
}



BinaryHeap::BinaryHeap(size_t size)
{
	this->tab = new Edge*[size];
	for (size_t i = 0;i < size;i++)
	{
		this->tab[i] = new Edge();
	}
	this->size = 0;
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
}

BinaryHeap::~BinaryHeap()
{
	for (size_t i = 0;i < this->size;i++)
	{
		delete this->tab[i];
	}
	delete[] this->tab;
	this->size = 0;
}

