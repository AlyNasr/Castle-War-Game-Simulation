#pragma once

#include"Enemies/Enemy.h"

class Node
{
private:
	Enemy* item;
	Node* next;

public:
	Node();
	Node(Enemy* anItem);
	Node(Enemy* anItem, Node* nextPtr);
	void setItem(Enemy* anItem);
	Enemy* getItem() const;
	void setNext(Node* nextPtr);
	Node* getNext() const;
};

