#pragma once

#include "Enemy.h"
class ShieldedFighter :public Enemy
{
private:
	double Priority;
	double C1, C2, C3;

public:
	ShieldedFighter(double c1, double c2, double c3, int id, color r_c, REGION r_region, double health, int arrival, double firepower, int reload, int d = MaxDistance);
	~ShieldedFighter();

	void CalculatePriority();
	double GetPriority() const;

	virtual void Move(const Tower& tower, int timestep);	  
	virtual void Attack(Tower& tower, int timestep);	   
};

