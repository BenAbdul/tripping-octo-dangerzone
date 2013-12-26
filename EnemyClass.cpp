#include"EnemyClass.h"
#include"Declarations.h"

int CurrentID = 0;
bool LazyFlag = false;

Enemy::Enemy()
{
	xPos = 0;
	yPos = 0;
	CurrentID++;
	ID = CurrentID;
	Random = (rand () % 80 + 20) / 10;
	LazyFlag = false;
	if(LazyFlag2 == false)
	{
		if ( PlayerXVel > 19 && PlayerX < 4400)
		{
			xPos = PlayerX + 900;
			yPos = PlayerY;
		}
		else if ( PlayerXVel < -19 && PlayerX > 1000)
		{
			xPos = PlayerX - 900;
			yPos = PlayerY;
		} 
		else if (PlayerYVel > 19 && PlayerY < 4600)
		{
			yPos = PlayerY + 700;
			xPos = PlayerX;
		}
		else if (PlayerYVel < -19 && PlayerY > 1200)
		{
			yPos = PlayerY - 700;
			xPos = PlayerX;
		}
		LazyFlag2 = true;
	}
	else
	{
		do {
			xPos = rand () % 5500 + 500;
			if (xPos < CameraX || xPos > CameraX + 800) LazyFlag = true;
		} while (LazyFlag == false);
		LazyFlag = false;

		do {
			yPos = rand () % 5500 + 500;
			if (yPos < CameraY || yPos > CameraY + 500) LazyFlag = true;
		} while(LazyFlag == false);
	}
	LazyFlag = false;
	Frame = 0;
	FrameTime = 0;
	xVel = 0;
	yVel = 0;
	Active = 1;
	Facing = 0;
}