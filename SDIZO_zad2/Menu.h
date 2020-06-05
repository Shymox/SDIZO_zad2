#pragma once
#include <string>
#include <string>
#include "List.h"
#include "BinaryHeap.h"
#include "Timer.h"
#include "Matrix.h"
#include "MatrixList.h"

class Menu
{
private:
	double time = 0;
	int page=0;
	int index=0;
	bool exit = true;
	const int SIZEX = 4;
	const int SIZEY = 3;

	std::string nazwa(int page);
	Matrix* matrixMST,* matrixPth;
	MatrixList* listMST,* listPth;
	Timer* timer;

public:
	void loadMST(std::string name);

	void loadPth(std::string name);

	void randomMST(size_t size,int prop,int max);

	void randomPth(size_t size,int prop,int max);

	void loop();

	void display();

	void input();

	void writeTime(double time);

	Menu();

	~Menu();
};

