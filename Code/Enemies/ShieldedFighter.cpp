#include "ShieldedFighter.h"
#include "..\Castle\Tower.h"

ShieldedFighter::ShieldedFighter(double c1, double c2, double c3, int id, color r_c, REGION r_region, double health, int arrival, double firepower, int reload, int d) :
	Enemy(id, r_c, r_region, health, arrival, firepower, reload, d)
{
	Priority = 0;
	C1 = c1;
	C2 = c2;
	C3 = c3;
}

ShieldedFighter::~ShieldedFighter() {}


void ShieldedFighter::Move(const Tower& tower, int timestep)
{
	int enemydistance = (Distance - 60) * -1;   // to easily compare the enemy distance and paved distance 
	                                            // as they increase in opposite directions
	
	if (enemydistance < tower.GetPavedDistance() / OneMeter)
		DecrementDist();
}        



void ShieldedFighter::Attack(Tower& tower, int timestep)    
{
	if (AttackTime == timestep) 
	{
		double towerHealth = tower.GetHealth();
		towerHealth -= (2 / (double)Distance) * FirePower;
		tower.SetHealth(towerHealth);
		AttackTime += ReloadPeriod + 1;
	}
	
}	

void ShieldedFighter::CalculatePriority() 
{	
	Priority = (FirePower / (double)Distance) * C1 + (C2 / 3.0) + Health * C3; 
}

double ShieldedFighter::GetPriority() const 
{
	return Priority;
}

