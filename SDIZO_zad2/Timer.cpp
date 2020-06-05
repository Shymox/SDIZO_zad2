#include "Timer.h"
#include <Windows.h>
#include <iostream>

/*
Klasa zawieraj¹ca pomiar czasu
*/

double frequency = 0.0;
__int64 counterstart = 0;
//Zeruje i startuje pomiar czasu
void Timer::startCounter()
{
LARGE_INTEGER largeInt;
if (!QueryPerformanceFrequency(&largeInt))
std::cout << "Blad pomiaru czasu!"<<'\n';

frequency = double(largeInt.QuadPart) / 1000.0;

QueryPerformanceCounter(&largeInt);
counterstart = largeInt.QuadPart;
}
//Wyœwietla wartoœæ pomiaru
double Timer::getCounter()
{
    LARGE_INTEGER largeInt;
    QueryPerformanceCounter(&largeInt);
    return double(largeInt.QuadPart - counterstart) / frequency;
}

Timer::Timer()
{

}

Timer::~Timer()
{

}
