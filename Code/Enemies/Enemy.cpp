#include "Enemy.h"

Enemy::Enemy(int id, color r_c, REGION r_region, double health, int arrival, double firepower, int reload, int d)
{
	ID = id;
	Clr = r_c;
	Region = r_region;
	Health = health;
	ArrivalTime = arrival;
	FirePower = firepower;
	ReloadPeriod = reload;
	SetDistance(d);
	AttackTime = arrival; //Initially attack time equals arrival time
}

int Enemy::GetID() const 
{
	return ID;
}

color Enemy::GetColor() const
{
	return Clr;
}

REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

void Enemy::SetHealth(double h) 
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Enemy::GetHealth() const 
{
	return Health;
}

int Enemy::GetArrivalTime() const 
{
	return ArrivalTime;
}

void Enemy::SetAttackTime(int t) 
{
	if (t >= 0)
		AttackTime = t;
}

int Enemy::GetAttackTime() const
{
	return AttackTime;
}

bool Enemy::IsKilled() 
{
	if (Health <= 0)
		return true;
	else
		return false;
}

Enemy::~Enemy()
{}

