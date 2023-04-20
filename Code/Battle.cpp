#include "Battle.h"

Battle::Battle()
{
	ActiveEnemyCount = 0;
	FileEnemyCount = 0;
	InactiveQueue = new Queue();
	KilledQueue = new Queue();
}

void Battle::DrawEnemies(GUI * pGUI)
{
	ActiveEnemyCount = 0;
	for (int i = 0; i < NoOfRegions; i++) 
	{
		(BCastle.GetTowers())[i].AddActiveEnemiesToDraw(BEnemiesForDraw, ActiveEnemyCount); //ActiveEnemyCount is sent by reference and updated
	}
	pGUI->DrawEnemies(BEnemiesForDraw, ActiveEnemyCount);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle::LoadFile() 
{
	Enemy** InactiveEnemies;  // Array of pointers to inactive enemies

	ifstream inputfile("input.txt");
	if (inputfile.is_open()) {
		
		// read the first line of the input file
		double TH; // tower health
		int N;     // maximum number of enemies a tower can shoot at a time step
		int TP;    // tower Power
		inputfile >> TH >> N >> TP;
		BCastle.SetTowersHealth(TH);
		BCastle.SetTowersN(N);
		BCastle.SetTowersFirePower(TP);

		// read the second line of the input file
		double C1, C2, C3;
		inputfile >> C1 >> C2 >> C3;
		 
		// read the third line which represents the number of enemies in the battle
		inputfile >> FileEnemyCount;
		InactiveEnemies = new Enemy * [FileEnemyCount];
		
		
		// read the enemies lines
		int id, type, arrivaltime, reload;
		double health, power;
		char reg;

		for (int i = 0; i < FileEnemyCount; i++) 
		{	
			inputfile >> id >> type >> arrivaltime >> health >> power >> reload >> reg;

			REGION region;
			switch (reg) {
			case 'A':
				region = A_REG;
				break;

			case 'B':
				region = B_REG;
				break;

			case 'C':
				region = C_REG;
				break;

			case 'D':
				region = D_REG;
				break;

			default:
				break;
			}

			switch (type)
			{
			case 0: // paver
				InactiveEnemies[i] = new Paver(id, DARKBLUE, region, health, arrivaltime, power, reload);
				InactiveQueue->enqueue(InactiveEnemies[i]);
				break;

			case 1: // fighter
				InactiveEnemies[i] = new Fighter(id, DARKOLIVEGREEN, region, health, arrivaltime, power, reload);
				InactiveQueue->enqueue(InactiveEnemies[i]);
				break;

			case 2: // Shielded fighter
				InactiveEnemies[i] = new ShieldedFighter(C1, C2, C3, id, ORANGERED, region, health, arrivaltime, power, reload);
				InactiveQueue->enqueue(InactiveEnemies[i]);
				break;

			default:
				break;
			}
		}
	}
}


void Battle::DrawPavedAreas(GUI * pGUI) 
{
	pGUI->DrawPavedArea(BCastle.GetTowers());
}

void Battle::UpdateTowersActiveQueues(int timestep) 
{
	while (1) {
		Enemy* temp = InactiveQueue->peekFront();

		if (temp != NULL) {
			if (temp->GetArrivalTime() <= timestep && temp->GetHealth() > 0) {
				InactiveQueue->dequeue();

				REGION region = temp->GetRegion();
				switch (region) {
				case A_REG:
					(BCastle.GetTowers())[0].GetActiveQueue()->enqueue(temp);
					break;

				case B_REG:
					(BCastle.GetTowers())[1].GetActiveQueue()->enqueue(temp);
					break;

				case C_REG:
					(BCastle.GetTowers())[2].GetActiveQueue()->enqueue(temp);
					break;

				case D_REG:
					(BCastle.GetTowers())[3].GetActiveQueue()->enqueue(temp);
					break;

				default:
					break;
				}
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
}

void Battle::MoveEnemies(int timestep) 
{
	for (int i = 0; i < NoOfRegions;i++) 
	{
		Node* curr = (BCastle.GetTowers())[i].GetActiveQueue()->getFront();

		while (curr != NULL) 
		{
			curr->getItem()->Move((BCastle.GetTowers())[i], timestep);
			curr = curr->getNext();
		}
	}
}

void Battle::TowersAttackEnemies()
{
	for (int i = 0; i < NoOfRegions;i++) 
	{
		(BCastle.GetTowers())[i].Attack();
	}
}

void Battle::EnemiesAttackTowers(int timestep)
{
	for (int i = 0; i < NoOfRegions;i++) 
	{
		Node* curr = (BCastle.GetTowers())[i].GetActiveQueue()->getFront();
		while (curr != NULL) 
		{
			curr->getItem()->Attack((BCastle.GetTowers())[i],timestep);
			curr = curr->getNext();
		}
	}
}

void Battle::UpdateKilledEnemies()
{
	for (int i = 0; i < NoOfRegions;i++) 
	{
		(BCastle.GetTowers())[i].MoveKilledEnemies(KilledQueue);
	}
}

bool Battle::IsGameLOSS() 
{
	for (int i = 0; i < NoOfRegions;i++) 
	{
		if (!(BCastle.GetTowers())[i].IsDamaged())
			return false;
	}
	return true;
}

bool Battle::IsGameWIN() 
{
	return (FileEnemyCount == KilledQueue->getSize());
}

void Battle::Simulate() 
{
	GUI* pGUI = new GUI;
	Point p;
	pGUI->PrintMessage("Welcome, Click at any point to start the war simulation ...");
	pGUI->GetPointClicked(p);

	LoadFile();

	int TimeStep = 1;
	while(1){

		UpdateTowersActiveQueues(TimeStep);
		
		pGUI->ClearBattleArea();
		pGUI->DrawCastle();
		DrawPavedAreas(pGUI);

		TowersAttackEnemies();

		UpdateKilledEnemies();

		EnemiesAttackTowers(TimeStep);

		DrawEnemies(pGUI);

		pGUI->PrintMessage("Time Step = " + to_string(TimeStep) + "      Active Enemies = " + to_string(ActiveEnemyCount)
			+ "      Killed Enemies = " + to_string(KilledQueue->getSize()));
		
		Sleep(500);

		MoveEnemies(TimeStep);

		if (IsGameLOSS()) {
			pGUI->PrintMessage("Castle was defeated! All towers were damaged.    Time Step = " + to_string(TimeStep) + "    Active Enemies = " + to_string(ActiveEnemyCount)
				+ "    Killed Enemies = " + to_string(KilledQueue->getSize()) + " .    Click at any point to exit...");
			pGUI->GetPointClicked(p);
			break;
		}

		if (IsGameWIN()) {
			pGUI->PrintMessage("Castle WON! All enemies were killed.    Time Step = " + to_string(TimeStep) 
				  + "    Killed Enemies = " + to_string(KilledQueue->getSize()) + " .    Click at any point to exit...");
			pGUI->GetPointClicked(p);
			break;
		}
		TimeStep++;
	}

	delete pGUI;
}

Battle::~Battle() 
{
	// deallocating any dynamically allocated enemies if any

	for (int i = 0; i < NoOfRegions; i++) 
	{
		int size = (BCastle.GetTowers())[i].GetActiveQueue()->getSize();
		if (size != 0) 
		{
			for (int j = 0; j < size; j++) 
			{
				Enemy* curr = (BCastle.GetTowers())[i].GetActiveQueue()->peekFront();
				if (curr) 
				{
					delete curr;
					curr = NULL;
				}
				(BCastle.GetTowers())[i].GetActiveQueue()->dequeue();
			}
		}
		
	}

	for (int i = 0; i < InactiveQueue->getSize(); i++) 
	{
		Enemy* curr = InactiveQueue->peekFront();
		if (curr) 
		{
			delete curr;
			curr = NULL;
		}
		InactiveQueue->dequeue();
	}
	delete InactiveQueue;


	for (int i = 0; i < KilledQueue->getSize(); i++)
	{
		Enemy* curr = KilledQueue->peekFront();
		if (curr)
		{
			delete curr;
			curr = NULL;
		}
		KilledQueue->dequeue();
	}
	delete KilledQueue;
}