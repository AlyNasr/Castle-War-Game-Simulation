#pragma once
#include "Enemy.h"

class Paver :  public Enemy
{
public:
	Paver(int id, color r_c, REGION r_region, double health, int arrival, double firepower, int reload, int d = MaxDistance/2);
	~Paver();

	virtual void Move(const Tower& tower, int timestep);
	virtual void Attack(Tower& tower, int timestep);	  
};

