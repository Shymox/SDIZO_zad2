#include "List.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>

/*
Klasa zawieraj¹ca Listê oraz funkcje potrzebne do jej obs³ugi
*/
//Usuwanie elementu z listy
void List::popElem(ListElem* elem)
{
	if (elem==head)
	{
		popFront();
		//std::cout << "b";
		return;
	}
	if (elem==tail)
	{
		//std::cout << "c";
		popBack();
		return;
	}
		elem->next->prev = elem->prev;
		elem->prev->next = elem->next;
		delete elem;
		this->size--;
}
//Utworzenie listy z losowych elementów o podanym rozmiarze
void List::random(int size)
{
	this->erase();
	/*for (int i = 0; i < size;i++)
	{
		pushBack(rand());
	}*/
}
//Za³adowanie listy z pliku
void List::load(std::string name)
{
	this->erase();
	/*std::fstream file;
	file.open(name, std::ios::in | std::ios::out);
	if (file.good() == true)
	{
		size_t size=0;
		std::cout << "Uzyskano dostep do pliku!" << std::endl;
		std::string data;
		getline(file, data);
		try {
			size = static_cast<size_t>(std::stoi(data));
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
			//	pushBack(static_cast<int>(std::stoi(data)));
			}
			catch (std::exception)
			{
				std::cout << "Blad odczytu: std::exception" << '\n';
			}
		}
		file.close();
		if ((this->size) < size)
		{
			this->erase();
			std::cout << "Blad odczytu: Rozmiar listy wiekszy niz ilosc danych" << '\n';
			this->size = 0;
		}
	}
	else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;*/
}
//Dodanie elementu na pocz¹tek listy
void List::pushFront(Node* node)
{
	ListElem* temp = new ListElem();
	temp->node = node;
	temp->prev = nullptr;
	temp->next = this->head;
	if (head != nullptr)
	{
		this->head->prev = temp;
	}
	else
	{
		this->tail = temp;
	}
	this->head = temp;
	this->size++;
}
//Dodanie elementu na koniec listy
void List::pushBack(Node* node)
{
	ListElem* temp = new ListElem();
	temp->node = node;
	temp->next = nullptr;
	temp->prev = this->tail;
	if (tail != nullptr)
	{
		this->tail->next = temp;
	}
	else
	{
		this->head = temp;
	}
	this->tail = temp;
	this->size++;
}
//Dodanie elementu na miejsce w liscie o podanym numerze
void List::push(Node* node, size_t index)
{	

	if (index == 0)
		{
			pushFront(node);
		} 
	else if (index == this->size)
		{
			pushBack(node);
		}
	else if (0 < index < this->size)
	{
		ListElem* temp = this->head;
		while (index)
		{
			temp = temp->next;
			index--;
		}
		ListElem* tmp = new ListElem();
		tmp->node = node;
		tmp->next = temp;
		tmp->prev = temp->prev;
		temp->prev->next = tmp;
		temp->prev = tmp;
		
		this->size++;
	}
}
//Usuniecie elementu z pocz¹tku listy
void List::popFront()
{
	if (this->head != nullptr)
	{	
		if (size == 1)
		{
			this->tail = nullptr;
			this->head = nullptr;
		}
		else if (size == 2)
		{
			ListElem* temp = this->head;
			delete temp;
			this->tail->prev = nullptr;
			this->head = tail;
		}
		else if (size != 0)
		{
			ListElem* temp = this->head;
			this->head = this->head->next;
			this->head->prev = nullptr;
			delete temp;
		}
		this->size--;
	}

}
//Usuniecie elementu z konca listy
void List::popBack()
{
	if (this->tail != nullptr)
	{
		this->size--;
		if (size == 0)
		{	
			this->tail = nullptr;
			this->head = nullptr;
			return;
		}
		if (size == 1)
		{
			ListElem* temp = this->tail;
			delete temp;
			this->head->next = nullptr;
			this->tail = head;
		}
		else if(size!=0)
		{
			ListElem* temp = this->tail;
			this->tail = this->tail->prev;
			this->tail->next = nullptr;
			delete temp;
		}
	}
}
//Usuniecie elementu o podanym indeksie
void List::pop(int index)
{
		if (index == 0)
		{
			popFront();
		}
		else if (index == size)
		{
			popBack();
		}
		else if (0 < index && index < size)
		{
			ListElem* temp = this->head;
			while (index)
			{
				temp = temp->next;
				index--;
			}
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			delete temp;
			this->size--;
		}
}
//usuniecie podanego numeru z listy
void List::popNumber(Node* number)
{
	if (this->head != nullptr)
	{
		ListElem* temp = this->head;
		while (temp != nullptr)
		{

			if (temp->node->nodeTo == number->nodeTo && temp->node->value == number->value)
			{
				ListElem* tmp =temp->next;
				popElem(temp);
				temp = tmp;
			}
			else
			{
				temp = temp->next;
			}
		}
	}

}
//wyszukiwanie wartosæi, jeœli znaleziono zwraca true
bool List::search(Node* number)
{
	if (this->head)
	{
		ListElem* temp = this->head;
		while (temp != nullptr)
		{
			if (temp->node == number) return true;
			temp = temp->next;
		}
	}
	return false;
}
bool List::search(int value, int nodeTo)
{
	if (this->head)
	{
		ListElem* temp = this->head;
		while (temp != nullptr)
		{
			if (temp->node->nodeTo == nodeTo && temp->node->value == value) return true;
			temp = temp->next;
		}
	}
	return false;
}
Node* List::makeNode(int nodeTo, int value)
{
	Node* node=new Node;
	node->nodeTo = nodeTo;
	node->value = value;
	return node;
}
bool List::isEmpty()
{
	if (this->size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
Node* List::returnFNode()
{
	if (this->head != nullptr)
	{
		return this->head->node;
	}
	return nullptr;
}
Node* List::returnNode(int i)
{
	ListElem* node=this->head;
	if (i < this->size)
	{
		for (int j = 0;j < i;j++)
		{
			node = node->next;
		}
		return node->node;
	}
	return 0;
}
ListElem* List::returnHead()
{
	return this->head;
}
//Wyœwietlanie listy
void List::display()
{
	ListElem* temp = this->head;
	while (temp != nullptr)
	{
		std::cout << "[" << temp->node->nodeTo << " " << temp->node->value << "]";
		temp =temp->next;

	}

}
//Wyœwietlanie listy w odwrotnej kolejnoœci
void List::display2()
{
	ListElem* temp = this->tail;
	while (temp != nullptr)
	{
		std::cout <<"["<< temp->node->nodeTo << " "<<temp->node->value<<"]";
		temp = temp->prev;

	}

}
//Kasowanie listy
void List::erase()
{	
	while (this->head != nullptr)
	{
		ListElem* temp = this->head;
		this->head = this->head->next;
		delete temp->node;
		delete temp;
	}
	this->size = 0;
	this->tail = nullptr;
}

List::List()
{
	this->size = 0;
	this->head=nullptr;
	this->tail=nullptr;
}

List::~List()
{
	this->erase();
}
