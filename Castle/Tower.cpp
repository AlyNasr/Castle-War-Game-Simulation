#include "Tower.h"
#include"..\Enemies\Enemy.h"
#include"..\Queue.h"
#include"..\Enemies\ShieldedFighter.h"

Tower::Tower() 
{
	PavedDistance = MaxDistanceInPixels/2; // Initially half of the 60 meters distance
	ActiveQueue = new Queue();
}

void Tower::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Tower::GetHealth() const
{
	return Health;
}

void Tower::SetRegion(REGION r) 
{
	Region = r;
}

REGION Tower::GetRegion() const 
{
	return Region;
}

void Tower::IncreasePavedDistance() 
{
	if(PavedDistance/OneMeter < 58)  // 58 is the maximum paved distance
		PavedDistance += PavedAdded;
}

int Tower::GetPavedDistance() const 
{
	return PavedDistance;
}

void Tower::SetFirePower(int fp) 
{
	FirePower = fp;
}

void Tower::setN(int n) 
{
	N = n;
}

void Tower::SortActiveQueue()
{
	if (ActiveQueue->isEmpty() || ActiveQueue->getSize() == 1) return; 

	Queue* temp = new Queue();
	Node* curr = ActiveQueue->getFront();
	while (curr != NULL) 
	{
		if (dynamic_cast<ShieldedFighter*>(curr->getItem())) // check if the enemy type is shielded fighter
		{ 
			temp->enqueue(curr->getItem());
		}
		curr = curr->getNext();
	}

	// update the priorities of shielded enemies in the temp queue
	curr = temp->getFront();
	for (int i = 0; i < temp->getSize(); i++) 
	{
		((ShieldedFighter*)curr->getItem())->CalculatePriority(); // down casting here is safe because the 
		                                                          // base class pointer points to derived class object
		curr = curr->getNext();
	}
	//
	
	// sort the shielded enemies in the temp queue according to their priorities
	int size = temp->getSize();
	while (size > 0) 
	{
		Node* max = temp->getFront();
		curr = max->getNext();
		for (int i = 1; i < size; i++) 
		{
			if (((ShieldedFighter*)curr->getItem())->GetPriority() > ((ShieldedFighter*)max->getItem())->GetPriority()) 
			{
				max = curr;
			}
			curr = curr->getNext();
		}
		temp->enqueue(max->getItem());
		temp->remove(max);
		size--;
	}
	//

	while (!ActiveQueue->isEmpty()) 
	{
		if (!dynamic_cast<ShieldedFighter*>(ActiveQueue->getFront()->getItem())) 
		{
			temp->enqueue(ActiveQueue->getFront()->getItem());
		}
		ActiveQueue->dequeue();
	}

	curr = temp->getFront();
	while (curr != NULL) {
		ActiveQueue->enqueue(curr->getItem());
		curr = curr->getNext();
		temp->dequeue();
	}

	delete temp;
}

Queue* Tower::GetActiveQueue()
{
	return ActiveQueue;
}

int Tower::GetActiveEnemiesCount() const 
{
	return ActiveQueue->getSize();
}

void Tower::Attack()
{
	if (Health > 0) 
	{
		SortActiveQueue();

		double health;     // enemy health
		double damage;     // damage caused by tower to the enemy, to be subtracted from the enemy health
		int k;             // constant for the damage equation, k = 2 for shielded fighters, k = 1 for others

		Node* curr = ActiveQueue->getFront();
		int n = 1;
		while (curr != NULL && n <= N)
		{
			health = curr->getItem()->GetHealth();

			if (dynamic_cast<ShieldedFighter*>(curr->getItem()))
				k = 2;
			else
				k = 1;

			damage = (1 / (double)curr->getItem()->GetDistance()) * FirePower * (1 / (double)k);
			health -= damage;
			curr->getItem()->SetHealth(health);

			curr = curr->getNext();
			n++;
		}
	}
}

void Tower::MoveKilledEnemies(Queue* killedqueue)
{
	Node* curr = ActiveQueue->getFront();
	while (curr != NULL)
	{
		if (curr->getItem()->GetHealth() <= 0)
		{
			killedqueue->enqueue(curr->getItem());
			Node* next = curr->getNext();
			ActiveQueue->remove(curr);
			curr = next;
		}
		else
		{
			curr = curr->getNext();
		}
	}
}

void Tower::AddActiveEnemiesToDraw(Enemy** BEnemiesForDraw, int& count) const
{
	Node* curr = ActiveQueue->getFront();
	while (curr != NULL) 
	{
		BEnemiesForDraw[count++] = curr->getItem();
		curr = curr->getNext();
	}
}

bool Tower::IsDamaged()
{
	return (Health == 0);
}

Tower::~Tower()
{
	delete ActiveQueue;
}
