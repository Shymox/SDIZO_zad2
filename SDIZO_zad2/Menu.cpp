#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include "List.h"
#include "BinaryHeap.h"
#include "Matrix.h"
#include "MatrixList.h"

/* 
Klasa Menu zawiera obs³ugê klawiatury oraz menu wraz z wywo³ywaniem wszystkich potrzebnych funkcji z innych klas
*/

std::string Menu::nazwa(int page)
{
	//Etykiety Menu
	switch (page)
	{
	case 0:
		return "Primm";
		break;
	case 1:
		return "Kruskal";
		break;
	case 2:
		return "Dijkstra";
		break;
	case 3:
		return "Ford-Bellman";
		break;
	case 4:
		return "Testy";
		break;
	}
}
//funkcja ³aduje graf nieskierowany z pliku
void Menu::loadMST(std::string name)
{
	size_t size;
	size_t number;
	std::fstream file;
	file.open(name, std::ios::in | std::ios::out);
	if (file.good() == true)
	{
		std::cout << "Uzyskano dostep do pliku!" << std::endl;
		std::string data;
		getline(file, data, ' ');
		try {
			number = static_cast<size_t>(std::stoi(data));
		}
		catch (std::exception)
		{
			std::cout << "B³ad odczytu: std::exception" << '\n';
		}
		getline(file, data);
		try {
			size = static_cast<size_t>(std::stoi(data));
		}
		catch (std::exception)
		{
			std::cout << "B³ad odczytu: std::exception" << '\n';
		}
		int i = 0;
		if ((size * (size - 1)) / 2 >= number)
		{
			this->matrixMST->init(size);
			this->listMST->init(size);
			size_t start, end;
			int weight;
			while (!file.eof() && i < number)
			{
				getline(file, data, ' ');
				try
				{
					start = static_cast<size_t>(std::stoi(data));
					if (start > size) break;
				}
				catch (std::exception)
				{
					std::cout << "Blad odczytu: std::exception" << '\n';
				}
				getline(file, data, ' ');
				try
				{
					end = static_cast<size_t>(std::stoi(data));
					if (end > size) break;
				}
				catch (std::exception)
				{
					std::cout << "Blad odczytu: std::exception" << '\n';
				}
				getline(file, data);
				try
				{
					weight = static_cast<int>(std::stoi(data));
				}
				catch (std::exception)
				{
					std::cout << "Blad odczytu: std::exception5" << '\n';
				}
				this->matrixMST->push(weight, start, end);
				this->matrixMST->push(weight, end, start);
				this->listMST->push(weight, start, end);
				this->listMST->push(weight, end, start);
				i++;
			}
		}
		file.close();
		if (i < number)
		{
			this->listMST->erase();
			this->matrixMST->erase();
			std::cout << "Blad odczytu: Rozmiar tablicy wiekszy niz ilosc danych" << '\n';
			
		}
	}
	else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
	system("pause");
}
//funkcja ³aduje graf skierowany z pliku
void Menu::loadPth(std::string name)
{
	size_t size;
	size_t number;
	std::fstream file;
	file.open(name, std::ios::in | std::ios::out);
	if (file.good() == true)
	{
		std::cout << "Uzyskano dostep do pliku!" << std::endl;
		std::string data;
		getline(file, data, ' ');
		try {
			number = static_cast<size_t>(std::stoi(data));
		}
		catch (std::exception)
		{
			std::cout << "B³ad odczytu: std::exception" << '\n';
		}
		getline(file, data);
		try {
			size = static_cast<size_t>(std::stoi(data));
		}
		catch (std::exception)
		{
			std::cout << "B³ad odczytu: std::exception" << '\n';
		}
		int i = 0;
		if ((size * (size - 1)) >= number)
		{
			this->matrixPth->init(size);
			this->listPth->init(size);
			size_t start, end;
			int weight;
			while (!file.eof() && i < number)
			{
				getline(file, data, ' ');
				try
				{
					start = static_cast<size_t>(std::stoi(data));
					if (start > size) break;
				}
				catch (std::exception)
				{
					std::cout << "Blad odczytu: std::exception" << '\n';
				}
				getline(file, data, ' ');
				try
				{
					end = static_cast<size_t>(std::stoi(data));
					if (end > size) break;
				}
				catch (std::exception)
				{
					std::cout << "Blad odczytu: std::exception" << '\n';
				}
				getline(file, data);
				try
				{
					weight = static_cast<int>(std::stoi(data));
				}
				catch (std::exception)
				{
					std::cout << "Blad odczytu: std::exception5" << '\n';
				}
				this->matrixPth->push(weight, start, end);
				this->listPth->push(weight, start, end);
				i++;
			}
		}
		file.close();
		if (i < number)
		{
			this->listPth->erase();
			this->matrixPth->erase();
			std::cout << "Blad odczytu: Rozmiar tablicy wiekszy niz ilosc danych" << '\n';
		}
	}
	else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
	system("pause");
}
//funkcja tworzy losowy graf nieskierowany o podanych parametrach
void Menu::randomMST(size_t size, int prop, int max)
{
	this->matrixMST->init(size);
	this->listMST->init(size);
	size_t maxNumber = 0;
	if ((((size * (size - 1)) / 2) * prop / 100) > (size - 1)) maxNumber = (((size * (size - 1)) / 2) * prop / 100) - (size - 1);
	List* list = new List();
	int k = rand() % max + 1;
	this->matrixMST->push(k, 0, 1);
	this->listMST->push(k, 0, 1);
	this->matrixMST->push(k, 1, 0);
	this->listMST->push(k, 1, 0);
	list->pushBack(list->makeNode(0, 1)); //utworzenie pierwszej krawêdzi
	list->pushBack(list->makeNode(1, 0));
		for (size_t i = 2;i < (size);i++) //utworzenie losowego drzewa rozpinaj¹cego
		{
			size_t j = rand() % i;
			k = rand() % max + 1;
			this->matrixMST->push(k,j, i);
			this->listMST->push(k,j, i);
			this->matrixMST->push(k, i, j);
			this->listMST->push(k, i, j);
			list->pushBack(list->makeNode(j, i));
			list->pushBack(list->makeNode(i, j));
		}
		List* list2 = new List();
		for (int i = 0;i < size; i++)
		{
			for (int j = size-1;j>i; j--) //utworzenie listy wszystkich mo¿liwych krawêdzi
			{
				if (i != j)
				{
					list2->pushBack(list->makeNode(i, j));
				}
			}
		}
		while (!list->isEmpty())
		{
			list2->popNumber(list->returnFNode()); //usuniêcie krawêdzi znajduj¹cych siê ju¿ w grafie
			list->popFront();
		}
		delete list;
		size_t i = 0;
		while (i < maxNumber)
		{
			if (rand() % 100 >=0) //losowanie czy dana krawêdz ma zostaæ dodana do grafu
			{
				int nodeTo=list2->returnFNode()->nodeTo;
				int nodeFrom=list2->returnFNode()->value;
				k = rand() % max + 1;
				this->matrixMST->push(k, nodeTo, nodeFrom);
				this->listMST->push(k, nodeTo, nodeFrom);
				this->matrixMST->push(k, nodeFrom, nodeTo);
				this->listMST->push(k, nodeFrom, nodeTo);
				i++;
				list2->popFront();
			}
			else
			{
				list2->pushBack(list2->returnFNode());
				list2->popFront();
			}
		}
		delete list2;
}
//funkcja tworzy losowy graf skierowany o podanych parametrach
void Menu::randomPth(size_t size, int prop, int max)
{
	this->matrixPth->init(size);
	this->listPth->init(size);
	size_t maxNumber = 0;
	if ((((size * (size - 1)) / 2) * prop / 100) > (size - 1)) maxNumber = (((size * (size - 1))) * prop / 100) - (size - 1);
	List* list = new List();
	int k = rand() % max + 1;
	this->matrixPth->push(k, 0, 1);
	this->listPth->push(k, 0, 1);
	list->pushBack(list->makeNode(0, 1)); //utworzenie pierwszej krawêdzi
	for (size_t i = 2;i < (size);i++) //utworzenie losowego drzewa rozpinaj¹cego
	{
		size_t j = rand() % i;
		k = rand() % max + 1;
		this->matrixPth->push(k, j, i);
		this->listPth->push(k, j, i);
		list->pushBack(list->makeNode(j, i));
	}
	List* list2 = new List();
	for (int i = 0;i < size; i++)
	{
		for (int j = 0;j <size; j++)//utworzenie listy wszystkich mo¿liwych krawêdzi
		{
			if (i != j)
			{
				list2->pushBack(list->makeNode(i, j));
			}
		}
	}
	while (!list->isEmpty())
	{
		list2->popNumber(list->returnFNode()); //usuniêcie krawêdzi znajduj¹cych siê ju¿ w grafie
		list->popFront();
	}
	delete list;
	size_t i = 0;
	while (i < maxNumber)
	{
		if (rand() % 100 >= 0) //losowanie czy dana krawêdz ma zostaæ dodana do grafu
		{
			int nodeTo = list2->returnFNode()->nodeTo;
			int nodeFrom = list2->returnFNode()->value;
			k = rand() % max + 1;
			this->matrixPth->push(k, nodeTo, nodeFrom);
			this->listPth->push(k, nodeTo, nodeFrom);
			i++;
			list2->popFront();
		}
		else
		{
			list2->pushBack(list2->returnFNode());
			list2->popFront();
		}
	}
	delete list2;

}
//Pêtla menu
void Menu::loop()
{
	while (exit)
	{
		this->display();
		this->input();
	}

}
//Wyœwietlanie menu
void Menu::display()
{
	std::cout << "=====Projekt SDiZO ZAD2======" << std::endl;
	std::cout << "==========CZERWIEC 2020===========" << std::endl;
	std::cout << "Sterowanie: a-lewo d-prawo w-gora s-dol Wyjscie-Esc" << std::endl;
	std::cout << "Wszystkie operacje sa wykonywane automatycznie dla macierzy i listy" << std::endl;
	std::cout << "Primm i Kruskal wspoldziela liste i macierz wierzcholkow" << std::endl;
	std::cout << "Dijkstra i BellmanFord wspoldziela liste i macierz wierzcholkow" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "<" << nazwa(page)<< ">" << std::endl;


	if (this->page == 4)
	{
		std::cout << "->" << "Testy" << std::endl;
	}
	else
	{
		switch (this->index)
		{
		case 0:
			std::cout << "->" << "Zbuduj z Pliku" << std::endl;
			std::cout << "  " << "Uzyj Algorytmu" << std::endl;
			std::cout << "  " << "Utworz Graf losowo" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			break;
		case 1:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "->" << "Uzyj Algorytmu" << std::endl;
			std::cout << "  " << "Utworz Graf losowo" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			break;
		case 2:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "  " << "Uzyj Algorytmu" << std::endl;
			std::cout << "->" << "Utworz Graf losowo" << std::endl;
			std::cout << "  " << "Wyswietl" << std::endl;
			break;
		case 3:
			std::cout << "  " << "Zbuduj z Pliku " << std::endl;
			std::cout << "  " << "Uzyj Algorytmu" << std::endl;
			std::cout << "  " << "Utworz Graf losowo" << std::endl;
			std::cout << "->" << "Wyswietl" << std::endl;
			break;
		}
	}

}
//Obs³uga klawiatury
void Menu::input()
{	
	
	char i = _getch();
	switch (i)
	{
	case 'a':
		if (this->page == 0)
		{
			this->page = SIZEX;
		}
		else
		{
			this->page--;
		}
		break;
	case 'd':
		if (this->page == SIZEX)
		{
			this->page = 0;
		}
		else
		{
			this->page++;
		}
		break;
	case 'w':
		if (this->index == 0)
		{
			this->index = SIZEY;
		}
		else
		{
			this->index--;
		}
		break;
	case 's':
		if (this->index == SIZEY)
		{
			this->index = 0;
		}
		else
		{
			this->index++;
		}
		break;
	case 13:
		switch (this->page)
		{

			int i, j, k;
		case 0:
			switch (this->index)
			{
			case 0:
			{
				std::cout << "Podaj nazwe pliku:\n";
				std::string name;
				std::cin >> name;
				this->loadMST(name);
			}
			break;

			case 1:
			{
				MST* primm;
				std::cout << "Czas dla macierzy:\n";
				this->timer->startCounter();
				primm = this->matrixMST->primm();
				std::cout << this->timer->getCounter();
				std::cout << "\nWynik dla macierzy:\n";
				primm->display();
				delete primm;
				std::cout << "\nCzas dla listy:\n";
				this->timer->startCounter();
				primm = this->listMST->primm();
				std::cout << this->timer->getCounter();
				std::cout << "\nWynik dla listy:\n";
				primm->display();
				system("pause");
				delete primm;
			}
			break;

			case 2:
				std::cout << "Podaj ilosc wierzcholkow" << '\n';
				std::cin >> i;
				std::cout << "Podaj % zapelnienia" << '\n';
				std::cin >> j;
				std::cout << "Podaj max wartosc krawedzi" << '\n';
				std::cin >> k;
				this->randomMST(i, j, k);
				break;

			case 3:
				this->matrixMST->display();
				std::cout << '\n';
				this->listMST->display();
				system("pause");
				break;
			}
			break;
		case 1:
				switch (this->index)
				{
				case 0:
				{
					std::cout << "Podaj nazwe pliku:\n";
					std::string name;
					std::cin >> name;
					this->loadMST(name);
				}
				break;
				case 1:
				{
					MST* kruskal;
					std::cout << "Czas dla macierzy:\n";
					this->timer->startCounter();
					kruskal = this->matrixMST->kruskal();
					std::cout << this->timer->getCounter();
					std::cout << "\nWynik dla macierzy:\n";
					kruskal->display();
					delete kruskal;
					std::cout << "\nCzas dla listy:\n";
					this->timer->startCounter();
					kruskal = this->listMST->kruskal();
					std::cout << this->timer->getCounter();
					std::cout << "\nWynik dla listy:\n";
					kruskal->display();
					system("pause");
					delete kruskal;
				}
				break;
				case 2:
					std::cout << "Podaj ilosc wierzcholkow" << '\n';
					std::cin >> i;
					std::cout << "Podaj % zapelnienia" << '\n';
					std::cin >> j;
					std::cout << "Podaj max wartosc krawedzi" << '\n';
					std::cin >> k;
					this->randomMST(i, j, k);
					break;
				case 3:
					this->matrixMST->display();
					std::cout << '\n';
					this->listMST->display();
					system("pause");
					break;
				}
				break;
		case 2:
				switch (this->index)
				{
				case 0:
				{
					std::cout << "Podaj nazwe pliku:\n";
					std::string name;
					std::cin >> name;
					this->loadPth(name);
				}
				break;
				case 1:
				{
					Pth* dijkstra;
					std::cout << "Czas dla macierzy:\n";
					this->timer->startCounter();
					dijkstra = this->matrixPth->dijkstra();
					std::cout << this->timer->getCounter();
					std::cout << "\nWynik dla macierzy:\n";
					dijkstra->display();
					delete dijkstra;
					std::cout << "\nCzas dla listy:\n";
					this->timer->startCounter();
					dijkstra = this->listPth->dijkstra();
					std::cout << this->timer->getCounter();
					std::cout << "\nWynik dla listy:\n";
					dijkstra->display();
					system("pause");
					delete dijkstra;
				}
				break;
				case 2:
					std::cout << "Podaj ilosc wierzcholkow" << '\n';
					std::cin >> i;
					std::cout << "Podaj % zapelnienia" << '\n';
					std::cin >> j;
					std::cout << "Podaj max wartosc krawedzi" << '\n';
					std::cin >> k;
					this->randomPth(i, j, k);
					break;
				case 3:
					this->matrixPth->display();
					std::cout << '\n';
					this->listPth->display();
					system("pause");
					break;
				}
				break;
		case 3:
				switch (this->index)
				{
				case 0:
				{
					std::cout << "Podaj nazwe pliku:\n";
					std::string name;
					std::cin >> name;
					this->loadPth(name);
				}
				break;
				case 1:
				{
					Pth* bellmanFord;
					std::cout << "Czas dla macierzy:\n";
					this->timer->startCounter();
					bellmanFord = this->matrixPth->bellmanFord();
					std::cout << this->timer->getCounter();
					std::cout << "\nWynik dla macierzy:\n";
					bellmanFord->display();
					delete bellmanFord;
					std::cout << "\nCzas dla listy:\n";
					this->timer->startCounter();
					bellmanFord = this->listPth->bellmanFord();
					std::cout << this->timer->getCounter();
					std::cout << "\nWynik dla listy:\n";
					bellmanFord->display();
					system("pause");
					delete bellmanFord;
				}
				break;
				case 2:
					std::cout << "Podaj ilosc wierzcholkow" << '\n';
					std::cin >> i;
					std::cout << "Podaj % zapelnienia" << '\n';
					std::cin >> j;
					std::cout << "Podaj max wartosc krawedzi" << '\n';
					std::cin >> k;
					this->randomPth(i, j, k);
					break;
				case 3:
					this->matrixPth->display();
					std::cout << '\n';
					this->listPth->display();
					system("pause");
					break;
				}
				break;
		case 4:
		{
			double timePrimmM = 0, timeKruskalM = 0, timeDijkstraM = 0, timeBellmanFordM= 0,
				timePrimmL= 0, timeKruskalL = 0, timeDijkstraL = 0, timeBellmanFordL = 0;
			int i, j, k,l;
			system("cls");
			std::cout << "Podaj ilosc testow" << '\n';
			std::cin >> l;
			std::cout << "Podaj ilosc wierzcholkow" << '\n';
			std::cin >> i;
			std::cout << "Podaj % zapelnienia" << '\n';
			std::cin >> j;
			std::cout << "Podaj max wartosc krawedzi" << '\n';
			std::cin >> k;
			for (int m = 0;m < l;m++)
			{
				MST* mst;
				Pth* pth;
				this->randomMST(i, j, k);
				this->randomPth(i, j, k);
				timer->startCounter();
				mst=matrixMST->primm();
				timePrimmM += timer->getCounter();
				timer->startCounter();
				mst = matrixMST->kruskal();
				timeKruskalM += timer->getCounter();
				timer->startCounter();
				pth=matrixPth->dijkstra();
				timeDijkstraM += timer->getCounter();
				timer->startCounter();
				pth = matrixPth->bellmanFord();
				timeBellmanFordM += timer->getCounter();
				timer->startCounter();
				mst = listMST->primm();
				timePrimmL += timer->getCounter();
				timer->startCounter();
				mst = listMST->kruskal();
				timeKruskalL += timer->getCounter();
				timer->startCounter();
				pth = listPth->dijkstra();
				timeDijkstraL += timer->getCounter();
				timer->startCounter();
				pth = listPth->bellmanFord();
				timeBellmanFordL += timer->getCounter();
				delete pth;
				delete mst;
			}
			timePrimmM = timePrimmM / l;
			timeKruskalM = timeKruskalM / l;
			timeDijkstraM = timeDijkstraM / l;
			timeBellmanFordM= timeBellmanFordM/l;

			timePrimmL = timePrimmL / l;
			timeKruskalL = timeKruskalL / l;
			timeDijkstraL = timeDijkstraL / l;
			timeBellmanFordL = timeBellmanFordL / l;

			std::cout << "Wynik Primm:\nMacierz: "<< timePrimmM<<"\nLista: "<<timePrimmL<<'\n';
			std::cout << "Wynik Kruskal:\nMacierz: " << timeKruskalM << "\nLista: " << timeKruskalL << '\n';
			std::cout << "Wynik Dijkstra:\nMacierz: " << timeDijkstraM << "\nLista: " << timeDijkstraL << '\n';
			std::cout << "Wynik BellmanFord:\nMacierz: " << timeBellmanFordM << "\nLista: " << timeBellmanFordL << '\n';

			std::cout << "Podaj nazwe pliku MST:\n";
			std::string nameMST;
			std::cin >> nameMST;
			std::cout << "Podaj nazwe pliku Pth:\n";
			std::string namePth;
			std::cin >> namePth;
			for (int m = 0;m < l;m++)
			{
				MST* mst;
				Pth* pth;
				this->randomMST(i, j, k);
				this->randomPth(i, j, k);
				timer->startCounter();
				mst = matrixMST->primm();
				timePrimmM += timer->getCounter();
				timer->startCounter();
				mst = matrixMST->kruskal();
				timeKruskalM += timer->getCounter();
				timer->startCounter();
				pth = matrixPth->dijkstra();
				timeDijkstraM += timer->getCounter();
				timer->startCounter();
				pth = matrixPth->bellmanFord();
				timeBellmanFordM += timer->getCounter();
				timer->startCounter();
				mst = listMST->primm();
				timePrimmL += timer->getCounter();
				timer->startCounter();
				mst = listMST->kruskal();
				timeKruskalL += timer->getCounter();
				timer->startCounter();
				pth = listPth->dijkstra();
				timeDijkstraL += timer->getCounter();
				timer->startCounter();
				pth = listPth->bellmanFord();
				timeBellmanFordL += timer->getCounter();
				delete pth;
				delete mst;
			}
			timePrimmM = timePrimmM / l;
			timeKruskalM = timeKruskalM / l;
			timeDijkstraM = timeDijkstraM / l;
			timeBellmanFordM = timeBellmanFordM / l;

			timePrimmL = timePrimmL / l;
			timeKruskalL = timeKruskalL / l;
			timeDijkstraL = timeDijkstraL / l;
			timeBellmanFordL = timeBellmanFordL / l;

			std::cout << "Wynik Primm:\nMacierz: " << timePrimmM << "\nLista: " << timePrimmL << '\n';
			std::cout << "Wynik Kruskal:\nMacierz: " << timeKruskalM << "\nLista: " << timeKruskalL << '\n';
			std::cout << "Wynik Dijkstra:\nMacierz: " << timeDijkstraM << "\nLista: " << timeDijkstraL << '\n';
			std::cout << "Wynik BellmanFord:\nMacierz: " << timeBellmanFordM << "\nLista: " << timeBellmanFordL << '\n';

			system("pause");
		}
			break;
		}
		break;
	case 27:
		_exit(0);
		break;
	}
	system("cls");
}

//Wyœwietla podan¹ wartoœæ czasu
void Menu::writeTime(double time)
{
	std::cout << "Czas operacji wynosil:" << time <<"ms "<<'\n';
	
}

//Inicjalizacja wszystkich u¿ywanych obiektów oraz uruchomienie pêtli
Menu::Menu()
{
	this->listPth = new MatrixList();
	this->listMST = new MatrixList();
	this->matrixPth = new Matrix();
	this->matrixMST = new Matrix();	
	this->timer = new Timer();
	this->loop();
}

Menu::~Menu()
{
	delete this->listPth;
	delete this->listMST;
	delete this->matrixPth;
	delete this->matrixMST;
	delete this->timer;
}
