#include "Fighter.h"
#include "..\Castle\Tower.h"

Fighter::Fighter(int id, color r_c, REGION r_region, double health, int arrival, double firepower, int reload, int d) :
	Enemy(id, r_c, r_region, health, arrival, firepower, reload, d) {}

Fighter::~Fighter() {}


void Fighter::Move(const Tower& tower, int timestep)
{
	int enemydistance = (Distance - 60) * -1;   // to easily compare the enemy distance and paved distance 
	                                            // as they increase in opposite directions

	if (enemydistance < tower.GetPavedDistance()/OneMeter)
		DecrementDist();
}



void Fighter::Attack(Tower& tower, int timestep)
{
	if (AttackTime == timestep)
	{
		double towerHealth = tower.GetHealth();
		towerHealth -= (1 / (double)Distance) * FirePower;
		tower.SetHealth(towerHealth);
		AttackTime += ReloadPeriod + 1;
	}
	
}
