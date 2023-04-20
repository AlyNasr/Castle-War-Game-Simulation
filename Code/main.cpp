#include "Battle.h"

int main()
{	
	Battle* pGameBattle = new Battle;
	pGameBattle->Simulate();
	delete pGameBattle;

	return 0;
}
