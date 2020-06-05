#include "Array.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>
/*
Klasa zawieraj¹ca Tablice oraz funkcje potrzebne do jej obs³ugi
*/
void Array::random(size_t size)
{
	int* temp = new int[size];
	
	for (size_t i = 0;i < size;i++)
	{
		temp[i] = std::rand();
	}
	delete[] this->array;
	this->array = temp;
	this->size = size;
}
//ladowanie tablicy z pliku
void Array::load(std::string name)
{
	std::fstream file;
	file.open(name, std::ios::in | std::ios::out);
	if (file.good() == true)
	{
		std::cout << "Uzyskano dostep do pliku!" << std::endl;
		std::string data;
		getline(file, data);
		try {
			this->size = static_cast<size_t>(std::stoi(data));
		}
		catch (std::exception)
		{
			std::cout << "B³¹d odczytu: std::exception" << '\n';
		}
		delete[] this->array;
		this->array = new int[this->size];
		int i = 0;
		while (!file.eof() && i < this->size)
		{
			
			getline(file, data);
			try
			{
				this->array[i++] = static_cast<int>(std::stoi(data));
			}
			catch (std::exception)
			{
				std::cout << "Bla d odczytu: std::exception" << '\n';
			}
		}
		file.close();
		if (i < this->size)
		{
			delete[] this->array;
			std::cout << "Blad odczytu: Rozmiar tablicy wiekszy niz ilosc danych" << '\n';
			this->array = new int[0];
			this->size = 0;
		}
	}
	else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
}
//dodanie na pocz¹tek tablicy
void Array::pushFront(int value)
{
	int* temp = new int[size+1];
	*temp = value;
	for (size_t i = 1;i <=size;i++)
	{
		temp[i] = this->array[i - 1];
	}
	delete[] this->array;
	this->size++;
	this->array = temp;
}
//dodanie na koniec tablicy
void Array::pushBack(int value)
{
	int* temp = new int[size + 1];
	temp[size]=value;
	for (size_t i = 0;i < size;i++)
	{
		temp[i] = this->array[i];
	}
	delete[] this->array;
	this->size++;
	this->array = temp;
}
//dodanie do tablicy na podanym indexie
void Array::push(int value, size_t index)
{
	if (index <= size)
	{
		int* temp = new int[size + 1];
		temp[index] = value;
		for (size_t i = 0;i < index;i++)
		{
			temp[i] = this->array[i];
		}
		for (size_t i = index;i < this->size;i++)
		{
			temp[i + 1] = this->array[i];
		}
		delete[] this->array;
		this->array = temp;
		this->size++;
	}
}
//usuniecie pierwszej liczby
void Array::popFront()
{
	if (size > 0)
	{
		this->size--;
		int* temp = new int[size];
		for (size_t i = 0;i < size;i++)
		{
			temp[i] =this->array[i + 1];
		}
		delete[] this->array;
		this->array = temp;
	}
}
//usuniecie ostatniej liczby
void Array::popBack()
{
	if (size > 0)
	{
		this->size--;
		int* temp = new int[size];
		for (size_t i = 0;i < size; i++)
		{
			temp[i] = this->array[i];
		}
		delete[] this->array;
		this->array = temp;
	}
}
//usuniecie liczby o podanym indexie
void Array::pop(int index)
{
	if (size > 0 && index<size)
	{
		this->size--;
		int* temp = new int[size];
		for (size_t i = 0;i < index;i++)
		{
			temp[i] = this->array[i];
		}
		for (size_t i = index;i < size;i++)
		{
			temp[i] = this->array[i + 1];
		}
		delete[] this->array;
		this->array = temp;
	}
}
//usuniecie podanej liczby
void Array::popNumber(int number)
{
	int index = 0;
	for (index = 0;index < this->size;index++)
	{
		if (this->array[index] == number)
		{
			this->size--;
			int* temp = new int[size];
			for (size_t i = 0;i < index;i++)
			{
				temp[i] = this->array[i];
			}
			for (size_t i = index;i < size;i++)
			{
				temp[i] = this->array[i + 1];
			}
			delete[] this->array;
			this->array = temp;
		}
	}

}
//wyszukanie podanej liczby (jesli znajdzie zwraca true)
bool Array::search(int number)
{
	for (int i = 0;i < this->size;i++)
	{
		if (this->array[i] == number)
		{
			return true;
		}
	}
	return false;
}
//podanie dlugosci tablicy
size_t Array::length()
{
	return this->size;
}

//wyswietlenie tablicy
void Array::display()
{
	for (size_t i = 0;i <this->size;i++)
	{
		std::cout << this->array[i] << " ";
	}
}

Array::Array()
{
	this->array = new int[0];
	this->size = 0;
}

Array::~Array()
{
	delete[] this->array;
}
