#include "GUI.h"

GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0);
	pWind->ChangeTitle("Castle War Game");
	DrawMenu();
	ClearStatusBar();
	ClearBattleArea();
	DrawCastle();
}

GUI::~GUI()
{
	delete pWind;
}

// Input Functions:

void GUI::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

// Output Functions:

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	 
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.5), msg); 
}

void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}

void GUI::DrawMenu() const
{
	pWind->SetPen(BROWN);
	pWind->SetFont(30, BOLD, BY_NAME, "Arial");
	pWind->DrawString(WindWidth/2.5,MenuBarHeight/3.5, "Castle War Simulation");

	//Draw a line under the menu bar
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);	
}

void GUI::ClearStatusBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}

void GUI::ClearBattleArea() const
{
	pWind->SetPen(LIGHTYELLOW, 3);
	pWind->SetBrush(LIGHTYELLOW);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}

void GUI::DrawCastle() const
{
	int L = CastleWidth / 2;

	// 1- Drawing the brown square of the castle
	pWind->SetPen(BROWN);
	pWind->SetBrush(BROWN);
	pWind->DrawRectangle(CastleStartX, CastleStartY, CastleEndX, CastleEndY);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the castle)
	pWind->SetPen(WHITE);
	pWind->DrawLine(WindWidth/2, YHalfBattleArea - CastleWidth/2, WindWidth/2, YHalfBattleArea + CastleWidth/2);
	pWind->DrawLine(WindWidth/2 - CastleWidth/2, YHalfBattleArea, WindWidth/2 + CastleWidth/2, YHalfBattleArea);

	// 4- Drawing the 4 white squares inside the castle (one for each tower)
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(CastleStartX + L/3, CastleStartY + L/3, CastleStartX + 2*L/3, CastleStartY + 2*L/3);
	pWind->DrawRectangle(CastleStartX + L/3, CastleEndY - L/3, CastleStartX + 2*L/3, CastleEndY - 2*L/3);
	pWind->DrawRectangle(CastleEndX - 2*L/3, CastleStartY + L/3, CastleEndX - L/3, CastleStartY + 2*L/3);
	pWind->DrawRectangle(CastleEndX - 2*L/3, CastleEndY - L/3, CastleEndX - L/3, CastleEndY - 2*L/3);

	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(BROWN);
	pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	pWind->DrawString(CastleStartX + 0.44*L, CastleStartY + 5*L/12, "A");
	pWind->DrawString(CastleStartX + 0.44*L, YHalfBattleArea + 5*L/12, "D");
	pWind->DrawString(WindWidth/2 + 0.44*L, CastleStartY + 5*L/12, "B");
	pWind->DrawString(WindWidth/2 + 0.44*L, YHalfBattleArea + 5*L/12, "C");

	// 6- Drawing the 2 vertical brown lines at distance 60
	// that is because some rounding errors may occur if you choose another width and height for the window
	// so we draw 2 vertical lines at distance 60 to mark it
	pWind->SetPen(BROWN);
	pWind->DrawLine(CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, MenuBarHeight,
		CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, WindHeight-StatusBarHeight);
	pWind->DrawLine(CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, MenuBarHeight,
		CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, WindHeight-StatusBarHeight);
}

void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{
	color clr = E.GetColor();
	REGION Region = E.GetRegion();
	int Distance = E.GetDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}

/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) const
{
	//draw enemies at each region 
	for(int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
		                        // else print number of enemy in the region
		bool draw=true;
		for(int distance = MaxDistance ; distance >= MinDistance ; distance--)
		{
			CountEnemies = 0;

			for(int i = 0 ; i < size ; i++)
			{	
				if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
				{
					CountEnemies++;
				}
			}
			if(CountEnemies > 15)
			{
				draw=false;
				break;
			}
		}
		if(draw)
		{
			for( int distance = MaxDistance ; distance > 1 ; distance-- )
			{
				CountEnemies=0;

				for(int i = 0 ; i < size ; i++)
				{	
					if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			PrintMessage("Cannot Draw Enemies of region " + to_string(region+1) + 
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}

void GUI::DrawPavedArea(const Tower* towers) const 
{

	pWind->SetPen(KHAKI);
	pWind->SetBrush(KHAKI);

	for (int i = 0; i < NoOfRegions; i++) {
		int distance = towers[i].GetPavedDistance();
		REGION R = towers[i].GetRegion();

		switch (R)
		{
		case A_REG:
			pWind->DrawRectangle(0, MenuBarHeight, distance, YHalfBattleArea - 1);
			break;

		case B_REG:
			pWind->DrawRectangle(WindWidth, MenuBarHeight, WindWidth - distance, YHalfBattleArea - 1);
			break;

		case C_REG:
			pWind->DrawRectangle(WindWidth, YHalfBattleArea + 1, WindWidth - distance, WindHeight - StatusBarHeight);
			break;

		case D_REG:
			pWind->DrawRectangle(0, YHalfBattleArea + 1, distance, WindHeight - StatusBarHeight);
			break;

		default:
			break;
		}
	}
}