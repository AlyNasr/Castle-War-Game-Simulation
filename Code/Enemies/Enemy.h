#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
class Tower;

// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{
protected:
	int ID;           //Each enemy has a unique ID 
	color Clr;	      //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;    //Region of this enemy
	int Distance;	  //Horizontal distance between enemy & the tower of its region
	                  //Always positive (ranges from 2 to 60)
	double Health;	  
	int ArrivalTime;
	double FirePower;
	int ReloadPeriod;
	int AttackTime;

public:
	Enemy(int id, color r_c, REGION r_region, double health, int arrival, double firepower, int reload, int d = MaxDistance);
	int GetID() const;
	color GetColor() const;
	REGION GetRegion() const;
	void DecrementDist();
	void SetDistance(int d);
	int GetDistance() const;
	void SetHealth(double h);
	double GetHealth() const;
	void SetAttackTime(int t);
	int GetAttackTime() const;
	int GetArrivalTime() const;
	bool IsKilled();

	// Virtual Functions:
	virtual void Move(const Tower& tower, int timestep) = 0;	  //All enemies can move
	virtual void Attack(Tower& tower, int timestep ) = 0;	      //All enemies can attack (attacking is paving or shooting)
	virtual ~Enemy();
};

