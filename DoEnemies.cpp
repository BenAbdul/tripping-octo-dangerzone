#include"DoEnemies.h"
#include<time.h>
#include"Declarations.h"
#include"Game.h"

bool LazyFlag = false;

int CurrentID = 0;
Enemy::Enemy()
{
	srand(time(NULL));
	xPos = 0;
	yPos = 0;
	CurrentID++;
	ID = CurrentID;
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
				if (PlayerX > CURRENTCLASS.xPos && PlayerX < CURRENTCLASS.xPos + 49 && PlayerY > CURRENTCLASS.yPos && PlayerY < CURRENTCLASS.yPos + 25) 	
				{
					Ded = true;
					KillerID = CURRENTCLASS.ID;
				}
				else if (PlayerX + 27 > CURRENTCLASS.xPos && PlayerX + 27 < CURRENTCLASS.xPos + 49 && PlayerY + 25 > CURRENTCLASS.yPos && PlayerY + 25 < CURRENTCLASS.yPos + 25) 	
				{
					Ded = true;
					KillerID = CURRENTCLASS.ID;
				}
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

							else if (XPOS + 11 > CURRENTCLASS.xPos && XPOS + 11 < CURRENTCLASS.xPos + 25 && YPOS + 11 > CURRENTCLASS.yPos && YPOS+11 < CURRENTCLASS.yPos + 49)
							{
								CURRENTCLASS.Active = 0;
								ACTIVE = 0;
							}
						}
					}
				}
				if(Ded == false)
				{
					if (CURRENTCLASS.xPos > PlayerX && CURRENTCLASS.xVel >= -5) CURRENTCLASS.xVel-=2;
					else if (CURRENTCLASS.xPos < PlayerX && CURRENTCLASS.xVel <= 5) CURRENTCLASS.xVel+=2;
					if (CURRENTCLASS.yPos > PlayerY && CURRENTCLASS.yVel >=-5) {CURRENTCLASS.yVel-=2; CURRENTCLASS.Facing = 0;}
					else if (CURRENTCLASS.yPos < PlayerY && CURRENTCLASS.yVel <= 5) {CURRENTCLASS.yVel+=2; CURRENTCLASS.Facing = 1;}
				}
				else
				{

					if (CURRENTCLASS.xVel > 0)
					{
						if(CURRENTCLASS.xVel - 0.05 < 0) CURRENTCLASS.xVel = 0;
						else CURRENTCLASS.xVel-=0.05;
					}
					
					else if (CURRENTCLASS.xVel < 0)
					{
						if(CURRENTCLASS.xVel + 0.05 > 0) CURRENTCLASS.xVel = 0;
						else CURRENTCLASS.xVel += 0.05;
					}

					if (CURRENTCLASS.yVel > 0)
					{
						if(CURRENTCLASS.yVel - 0.05 < 0) CURRENTCLASS.yVel = 0;
						else CURRENTCLASS.yVel -= 0.05;
					}
				
					else if (CURRENTCLASS.yVel < 0)
					{
						if(CURRENTCLASS.yVel + 0.05 > 0) CURRENTCLASS.yVel = 0;
						else CURRENTCLASS.yVel += 0.05;
					}
				}

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
				CURRENTCLASS.xPos += CURRENTCLASS.xVel;
				CURRENTCLASS.yPos += CURRENTCLASS.yVel;
				ApplySurface(CURRENTCLASS.xPos - CameraX, CURRENTCLASS.yPos - CameraY,FrontDed,Screen);
				if (CURRENTCLASS.xVel > 0)
				{
					if(CURRENTCLASS.xVel - 0.1 < 0) CURRENTCLASS.xVel = 0;
					else CURRENTCLASS.xVel-=0.1;
				}
				
				else if (CURRENTCLASS.xVel < 0)
				{
					if(CURRENTCLASS.xVel + 0.1 > 0) CURRENTCLASS.xVel = 0;
					else CURRENTCLASS.xVel += 0.1;
				}

				if (CURRENTCLASS.yVel > 0)
				{
					if(CURRENTCLASS.yVel - 0.1 < 0) CURRENTCLASS.yVel = 0;
					else CURRENTCLASS.yVel -= 0.1;
				}
				
				else if (CURRENTCLASS.yVel < 0)
				{
					if(CURRENTCLASS.yVel + 0.1 > 0) CURRENTCLASS.yVel = 0;
					else CURRENTCLASS.yVel += 0.1;
				}
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