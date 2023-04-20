#pragma once
#include "Enemy.h"

class Fighter :  public Enemy
{
public:
	Fighter(int id, color r_c, REGION r_region, double health, int arrival, double firepower, int reload, int d = MaxDistance);
	~Fighter();

	virtual void Move(const Tower& tower, int timestep);
	virtual void Attack(Tower& tower, int timestep);
};

