#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "Tower.h"

class Castle
{
private:
	Tower Towers[NoOfRegions];

public:
	Castle();
	void SetTowersHealth(double h);
	void SetTowersFirePower(int fp);
	void SetTowersN(int n);          // set N which is the maximum number of enemies a tower can shoot at one time step 
	Tower* GetTowers();
};
