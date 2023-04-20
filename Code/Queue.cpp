#include "Queue.h"

Queue::Queue() 
{
	front = NULL;
	back = NULL;
	size = 0;
}

bool Queue::isEmpty() const
{
	return (size == 0);
}

bool Queue::enqueue(Enemy* newItem) 
{
	Node* newNode = new Node(newItem);

	if (isEmpty()) 
		front = newNode;
	else 
		back->setNext(newNode);
	
	back = newNode;
	size++;

	return true;
}

bool Queue::dequeue() 
{
	if (isEmpty()) return false;

	Node* toRemove = front;

	if (front == back) 
	{
		front = NULL;
		back = NULL;
	}
	else 
		front = front->getNext();
	
	toRemove->setNext(NULL);
	delete toRemove;
	toRemove = NULL;
	size--;

	return true;
}

bool Queue::remove(Node* anItem) 
{
	if (isEmpty()) return false;

	Node* toRemove = front;

	if (size == 1) 
	{ 
		front = NULL;
		back = NULL;
		toRemove->setNext(NULL);
		delete toRemove;
		toRemove = NULL;
		size--;
		return true;
	}
   
	if (front->getItem()->GetID() == anItem->getItem()->GetID())  // if the node to be removed is the first one
	{
		front = front->getNext();
		toRemove->setNext(NULL);
		delete toRemove;
		toRemove = NULL;
		size--;
		return true;
	}

	while (toRemove != NULL) 
	{
		if (toRemove->getItem()->GetID() == anItem->getItem()->GetID()) break;
		toRemove = toRemove->getNext();
	}

	Node* prev = front;
	while (prev != NULL) 
	{
		if (prev->getNext() == toRemove) break;
		prev = prev->getNext();
	}

	if(toRemove && prev)
		prev->setNext(toRemove->getNext());
	
	toRemove->setNext(NULL);
	delete toRemove;
	toRemove = NULL;
	prev = NULL;
	size--;

	return true;
}

Enemy* Queue::peekFront() 
{
	if (isEmpty()) return NULL;

	return front->getItem();
}

Node* Queue::getFront() 
{
	return front;
}

int Queue::getSize() const 
{
	return size;
}
