#pragma once
#include <string>
class Array
{
private:
	int* array;
	size_t size;
public:
	void random(size_t size);

	void load(std::string name);

	void pushFront(int value);

	void pushBack(int value);

	void push(int value, size_t index);

	void popFront();

	void popBack();

	void pop(int index);

	void popNumber(int number);

	bool search(int number);

	size_t length();

	void display();
	Array();

	~Array();

};

