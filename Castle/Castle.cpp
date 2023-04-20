#include "Castle.h"
#include "..\GUI\GUI.h"

Castle::Castle()
{
	Towers[0].SetRegion(A_REG);
	Towers[1].SetRegion(B_REG);
	Towers[2].SetRegion(C_REG);
	Towers[3].SetRegion(D_REG);
}

void Castle::SetTowersHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
	}
}

void Castle::SetTowersFirePower(int fp) 
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetFirePower(fp);
	}
}

void Castle::SetTowersN(int n) 
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].setN(n);
	}
}

Tower* Castle::GetTowers() 
{
	return Towers;
}


