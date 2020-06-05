#include "BST.h"
#include <fstream>
#include<iostream>
/*
Klasa zawieraj¹ca drzewo BST oraz funkcje potrzebne do jego obs³ugi
*/

void BST::rotateRight(TreeElem* node)
{
	if (node == this->root)
	{
		TreeElem* temp;
		temp = root;
		this->root = this->root->left;
		this->root->parent = nullptr;
		temp->parent = root;
		temp->left = root->right;
		this->root->right = temp;
	}
	else
	{
		TreeElem* temp;
		temp = node->left->right;
		node->left->parent = node->parent;
		node->left->right = node;
		node->left = temp;
	}
}

void BST::rotateLeft(TreeElem* node)
{
	if (node == this->root)
	{
		TreeElem* temp;
		temp = root;
		this->root = this->root->right;
		this->root->parent = nullptr;
		temp->parent = root;
		temp->right = root->left;
		this->root->left = temp;
	}
	else
	{
		TreeElem* temp;
		temp = node->right->left;
		node->right->parent = node->parent;
		node->right->left = node;
		node->right = temp;
	}
}

void BST::load(std::string name)
{
	this->erase();
	std::fstream file;
	file.open(name, std::ios::in | std::ios::out);
	if (file.good() == true)
	{
		size_t size = 0;
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
		int i = 0;
		while (!file.eof() && i<size)
		{
			getline(file, data);
			try
			{
				this->push(static_cast<int>(std::stoi(data)));
			}
			catch (std::exception)
			{
				std::cout << "Blad odczytu: std::exception" << '\n';
			}
			i++;
		}
		file.close();
		if (i < size)
		{
			std::cout << "Blad odczytu: Rozmiar listy wiekszy niz ilosc danych" << '\n';
			this->erase();
		}
	}
	else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
}

void BST::random(int size)
{
	this->erase();
	for (int i = 0;i < size;i++)
	{
		this->push(rand());
	}
}

void BST::insertFix(TreeElem* node)
{

}

void BST::deletefix(TreeElem* node)
{

}

void BST::push(int value)
{
	
	if (root == nullptr)
	{
		TreeElem* temp = new TreeElem;
		temp->parent = nullptr;
		temp->value = value;
		temp->left = nullptr;
		temp->right = nullptr;
		root = temp;
	}
	else
	{
		TreeElem* temp = this->root;
		TreeElem* tmp = temp;
		while (temp != nullptr)
		{
			tmp = temp;
			if (temp->value > value)
			{
				temp = temp->left;
			}
			else
			{
				temp = temp->right;
			}
		}
		delete temp;
		if (tmp->value > value)
		{
			temp = new TreeElem();
			temp->left = nullptr;
			temp->right = nullptr;
			temp->parent = tmp;
			temp->value = value;
			tmp->left = temp;
		}
		else
		{
			temp = new TreeElem();
			temp->left = nullptr;
			temp->right = nullptr;
			temp->parent = tmp;
			temp->value = value;
			tmp->right = temp;
		}
	}
}

void BST::pop(TreeElem* node)
{	
 	if (node != nullptr)
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			if (node == root)
			{	
				this->root = nullptr;
			}
			else
			{
				if (node == node->parent->left)
				{
					node->parent->left = nullptr;
				}
				else
				{
					node->parent->right = nullptr;
				}
			}
		}
		else
		{
				if (node->right == nullptr)
				{
					if (node != this->root)
					{
						node->left->parent = node->parent;
						if (node->parent->left == node)
						{
							node->parent->left = node->left;
						}
						else
						{
							node->parent->right = node->left;
						}
					}
					else
					{
						this->root = this->root->left;
						this->root->parent = nullptr;
					}
				}
				else
				{
					TreeElem* temp = node;
					node = node->right;
					TreeElem* tmp = node;
					while (tmp != nullptr)
					{
						node = tmp;
						tmp = tmp->left;
					}
					temp->value = node->value;
					
					if (node->right != nullptr)
					{
						node->right->parent = node->parent;
						if (temp->right == node)
						{
							node->parent->right = node->right;
						}
						else
						{
							node->parent->left = node->right;
						}
					}
					else
					{
						if (temp->right == node)
						{
							temp->right = nullptr;
						}
						else
						{
							node->parent->left = nullptr;
						}
					}
				}
		}
		delete node;
	}
}

bool BST::search(int number)
{
	TreeElem* temp = this->root;
	while (temp != nullptr)
	{
		if (temp->value == number)
		{
			return true;
		}
		if (number < temp->value)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}

	}
	return false;
}

void BST::erase()
{
	while (this->root!=nullptr)
	{
		pop(this->root);
	}
}

void BST::display(std::string sp, std::string sn, TreeElem* node)
{

	std::string s;
		if (node !=nullptr)
		{
			s = sp;
			if (sn == cr) s[s.length() - 2] = ' ';
			display(s + cp, cr, node->right);

			s = s.substr(0, sp.length() - 2);
			std::cout << s << sn << node->value << std::endl;

			s = sp;
			if (sn == cl) s[s.length() - 2] = ' ';
			display(s + cp, cl, node->left);
	}
}

TreeElem* BST::returnRoot()
{

	return root;
}

TreeElem* BST::findNode(int value)
{
	TreeElem* temp = this->root;
	while (temp != nullptr)
	{
		if (temp->value == value)
		{
			return temp;
		}
		if (value < temp->value)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	return temp;
}

BST::BST()
{
	this->root = nullptr;
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
}

BST::~BST()
{
	this->erase();
}
