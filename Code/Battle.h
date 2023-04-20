#pragma once

#include "Enemies\Enemy.h"
#include"Enemies/Paver.h"
#include"Enemies/Fighter.h"
#include"Enemies/ShieldedFighter.h"
#include "Castle\Castle.h"
#include<fstream>
#include<string>
#include"Queue.h"

// it is the controller of the project
class Battle
{
private:
	Castle BCastle;
	int ActiveEnemyCount;	                // The active number of enemies at each time step in the game
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Queue* InactiveQueue; // Stores the enemies from the input file in ascending order according to arrival time
	int FileEnemyCount;   // number of enemies in the input file
	Queue* KilledQueue;

public:
	Battle();
	void DrawEnemies(GUI * pGUI);
	void DrawPavedAreas(GUI* pGUI);
	Castle * GetCastle();
	void LoadFile();
	void UpdateTowersActiveQueues(int timestep);
	void MoveEnemies(int timestep);
	void TowersAttackEnemies();
	void EnemiesAttackTowers(int timestep);
	void UpdateKilledEnemies();
	bool IsGameLOSS();
	bool IsGameWIN();
	void Simulate();
	~Battle();
};

