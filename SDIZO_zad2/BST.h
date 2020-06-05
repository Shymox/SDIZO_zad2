#pragma once
#define BLACK true;
#define RED false;
#include <string>

struct TreeElem
{

	int value;

	TreeElem* parent, * left, * right;

};
class BST
{
private:
	TreeElem* root;

	std::string cr, cl, cp;

	void rotateLeft(TreeElem* node);

	void rotateRight(TreeElem* node);

public:
	void load(std::string name);

	void random(int size);

	void insertFix(TreeElem* node);

	void deletefix(TreeElem* node);

	void push(int value);

	void pop(TreeElem* node);

	bool search(int number);

	void erase();

	void display(std::string sp, std::string sn, TreeElem* node);

	TreeElem* returnRoot();

	TreeElem* findNode(int value);

	BST();

	~BST();
};

