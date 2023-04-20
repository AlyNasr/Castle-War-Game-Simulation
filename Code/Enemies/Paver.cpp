#include "Paver.h"
#include "..\Castle\Tower.h"

Paver::Paver(int id, color r_c, REGION r_region, double health, int arrival, double firepower, int reload, int d):
	Enemy(id, r_c, r_region, health, arrival, firepower, reload, d){}

Paver::~Paver(){}

void Paver::Move(const Tower& tower, int timestep)
{
	int enemydistance = (Distance - 60) * -1;   // to easily compare the enemy distance and paved distance 
	                                            // as they increase in opposite directions
	if (enemydistance < tower.GetPavedDistance()/OneMeter || AttackTime == timestep)
		DecrementDist();
}

void Paver::Attack(Tower& tower, int timestep)
{
	if (AttackTime == timestep) {		
		double c = FirePower;
		while (c > 0) 
		{
			Move(tower, timestep);
			tower.IncreasePavedDistance();
			c--;
		}
		AttackTime += ReloadPeriod + 1;
	}
}	 
