#include"DoEnemies.h"
#include<time.h>
#include"Declarations.h"

bool LazyFlag = false;

Enemy::Enemy()
{
	srand(time(NULL));
	xPos = 0;
	yPos = 0;

	do
	{
		xPos = rand () % 4900 + 100;
		if (xPos < CameraX || xPos > CameraX + 500) LazyFlag = true;
	} while (LazyFlag == false);
	LazyFlag = false;

	do
	{
		yPos = rand () % 4900 + 100;
		if (yPos < CameraY || yPos > CameraY + 500) LazyFlag = true;
	} while(LazyFlag == false);

	LazyFlag = false;
	SpareStream.str("");
	SpareStream << "New enemy created at (" << xPos << "," << yPos <<")";
	OpenDebugWindow(SpareStream.str());
	Frame = 0;
	FrameTime = 0;
	xVel = 0;
	yVel = 0;
	Active = 1;
	Facing = 0;
}

std::vector<Enemy> EnemyVector;


#define CURRENTCLASS EnemyVector.at(x)
#define XPOS		ProjectileVector.at(y)
#define YPOS		ProjectileVector.at(y + 1)
#define FRAME		ProjectileVector.at(y + 2)
#define FRAMETIME	ProjectileVector.at(y + 3)
#define XRATIO		ProjectileVector.at(y + 4)
#define YRATIO		ProjectileVector.at(y + 5)
#define ACTIVE		ProjectileVector.at(y + 6)
//Enemy clip size 49x36
//Collision size 49x25
void DoEnemies()
{
	if(EnemyVector.size() >= 1)
	{
		for(int x = 0; x < EnemyVector.size(); x++)
		{
			if(CURRENTCLASS.Active == 1)
			{
				if (ProjectileVector.size() > 1)
				{
					for(int y = 0; y <= ProjectileVector.size() - 7; y += 7)
					{
						if (ACTIVE == 1)
						{
							if (XPOS > CURRENTCLASS.xPos && XPOS < CURRENTCLASS.xPos + 25 && YPOS > CURRENTCLASS.yPos && YPOS < CURRENTCLASS.yPos + 49)
							{
								CURRENTCLASS.Active = 0;
								ACTIVE = 0;
							}
						}
					}
				}
				
				if (CURRENTCLASS.xPos > PlayerX && CURRENTCLASS.xVel >= -1) CURRENTCLASS.xVel--;
				else if (CURRENTCLASS.xPos < PlayerX && CURRENTCLASS.xVel <= 1) CURRENTCLASS.xVel++;
				if (CURRENTCLASS.yPos > PlayerY && CURRENTCLASS.yVel >=-1) {CURRENTCLASS.yVel--; CURRENTCLASS.Facing = 0;}
				else if (CURRENTCLASS.yPos < PlayerY && CURRENTCLASS.yVel <= 1) {CURRENTCLASS.yVel++; CURRENTCLASS.Facing = 1;}
				CURRENTCLASS.xPos += CURRENTCLASS.xVel;
				CURRENTCLASS.yPos += CURRENTCLASS.yVel;
				CURRENTCLASS.FrameTime++;
				if(CURRENTCLASS.FrameTime == 10)
				{
					CURRENTCLASS.FrameTime = 0;
					CURRENTCLASS.Frame++;
					if (CURRENTCLASS.Frame == 7) CURRENTCLASS.Frame = 0;
				}
				if (CURRENTCLASS.Facing == 1) ApplySurface(CURRENTCLASS.xPos - CameraX, CURRENTCLASS.yPos - CameraY,EnemyDownClips,Screen,&EnemyDownClipRect[CURRENTCLASS.Frame]);
				else ApplySurface(CURRENTCLASS.xPos - CameraX, CURRENTCLASS.yPos - CameraY,EnemyUpClips,Screen,&EnemyDownClipRect[CURRENTCLASS.Frame]);
			}
			else
			{
				ApplySurface(CURRENTCLASS.xPos - CameraX, CURRENTCLASS.yPos - CameraY,FrontDed,Screen);
			}
		}
	}
}
void CreateEnemy()
{
	Enemy TopLel;
	SpareStream.str("");
	SpareStream << "New enemy created at (" << TopLel.xPos << "," << TopLel.yPos <<")";
	OpenDebugWindow(SpareStream.str());
	EnemyVector.push_back(TopLel);
}