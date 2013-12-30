#include"EnemyClass.h"
#include"Declarations.h"

int CurrentID = 0;

Enemy::Enemy()
{
	xPos = rand () % 5500 + 500;
	yPos = rand () % 5500 + 500;
	CurrentID++;
	ID = CurrentID;
	Random = (rand () % 80 + 20) / 10;
	if ( PlayerXVel > 19 && PlayerX < 4400 && LazyFlag2 == false)
	{
		xPos = PlayerX + 900;
		yPos = PlayerY;
		LazyFlag2 = true;
	}
	else if ( PlayerXVel < -19 && PlayerX > 1000 && LazyFlag2 == false)
	{
		xPos = PlayerX - 900;
		yPos = PlayerY;
		LazyFlag2 = true;
	} 
	else if (PlayerYVel > 19 && PlayerY < 4600 && LazyFlag2 == false)
	{
		yPos = PlayerY + 700;
		xPos = PlayerX;
		LazyFlag2 = true;
	}
	else if (PlayerYVel < -19 && PlayerY > 1200 && LazyFlag2 == false)
	{
		yPos = PlayerY - 700;
		xPos = PlayerX;
		LazyFlag2 = true;
	}
	else
	{
		if (xPos > CameraX && xPos && xPos < CameraX + 800 && yPos > CameraY &&  yPos < CameraY + 600)
		{
			bool XIsDone = false;
			bool YIsDone = false;
			while (1)
			{
				if (XIsDone == false)
				{
					xPos = rand () % 5500 + 500;
					if (xPos < CameraX || xPos > CameraX + 800) XIsDone = true;
				}
				if(YIsDone == false)
				{
					yPos = rand () % 5500 + 500;
					if (yPos < CameraY || yPos > CameraY + 600) YIsDone = true;
				}
				else if (XIsDone == true) break; //My programming skillz know no bounds
			}
		}
	}

	Frame = 0;
	FrameTime = 0;
	xVel = 0;
	yVel = 0;
	Active = 1;
	Facing = 0;
}