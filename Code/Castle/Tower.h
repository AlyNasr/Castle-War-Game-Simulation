#pragma once

#include "..\Defs.h"
class Queue;
class Enemy;

class Tower
{
private:
	double Health;
	REGION Region;
	int PavedDistance;
	int FirePower;
	int N;                 // maximum number of enemies a tower can attack at one time step
	Queue* ActiveQueue;    // queue of the active enemies (updated every time step)

public:
	Tower();
	void SetHealth(double h);
	double GetHealth() const;
	void SetRegion(REGION r);
	REGION GetRegion() const;
	void IncreasePavedDistance();
	int GetPavedDistance() const;
	void SetFirePower(int fp);
	void setN(int n);
	void SortActiveQueue();
	Queue* GetActiveQueue();
	int GetActiveEnemiesCount() const;          // returns the number of active enemies at the current time step
	void Attack();
	void MoveKilledEnemies(Queue* killedqueue); // moves the killed enemies from active queue to killed queue
	void AddActiveEnemiesToDraw(Enemy** BEnemiesForDraw, int& count) const;
	bool IsDamaged();
	~Tower();
};

