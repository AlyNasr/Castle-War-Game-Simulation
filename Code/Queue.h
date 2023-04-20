#pragma once

#include"Node.h"

class Queue
{
private:
	Node* front;
	Node* back;
	int size;

public:
	Queue();
	bool isEmpty() const;
	bool enqueue(Enemy* newItem);
	bool dequeue();
	bool remove(Node* anItem);
	Enemy* peekFront();
	Node* getFront();
	int getSize() const;
};

