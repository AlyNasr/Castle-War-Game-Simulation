#pragma once

#define NoOfRegions 4
#define MaxDistance  60         // the maximum distance between any enemy and its tower
#define MaxDistanceInPixels 480 // the maximum distance between any enemy and its tower in Pixels = CastleStartX/2
#define PavedAdded 8            // the paved distance added by a paver at a single timestep in pixels = (CastleStartX/2)/MaxDistance
#define OneMeter 8              // 1 meter unit distance = 8 pixels 
#define MinDistance  2          // the minimum distance between any enemy and its tower
#define MaxVerticaEnemies  15   // the maximum number of enemies that can be drawn
		                        // if they are in the same region and same distance
								// (will be drawn vertical to each other)
#define MaxEnemyCount 300       // the maximum number of enemies the application can work on


//The four regions: A, B, C , and D
enum REGION {	
	A_REG,
	B_REG,
	C_REG,
	D_REG
};

struct Point
{
	int x;
	int y;
	Point(int a=0, int b=0)	//constructor
	{ x=a;	y=b;	}
};