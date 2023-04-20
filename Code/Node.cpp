#include "Node.h"

Node::Node() 
{
	item = NULL;
	next = NULL;
}

Node::Node(Enemy* anItem)
{
	item = anItem;
	next = NULL;
}

Node::Node(Enemy* anItem, Node* nextPtr)
{
	item = anItem;
	next = nextPtr;
}

void Node::setItem(Enemy* anItem)
{
	item = anItem;
}

Enemy* Node::getItem() const
{
	return item;
}

void Node::setNext(Node* nextPtr) 
{
	next = nextPtr;
}

Node* Node::getNext() const 
{
	return next;
}