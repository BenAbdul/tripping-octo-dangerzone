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
	do {
		xPos = rand () % (CameraX + 1000) + (CameraX - 150);
		if (xPos < CameraX || xPos > CameraX + 800) LazyFlag = true;
	} while (LazyFlag == false);
	LazyFlag = false;

	do {
		yPos = rand () % (CameraY + 700) + (CameraY - 150);
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
			if (CURRENTCLASS.yPos < 500) {CURRENTCLASS.yPos = 500; CURRENTCLASS.yVel = 0;}
			else if (CURRENTCLASS.yPos + 36 > 5500) {CURRENTCLASS.yPos = 5500 - 36; CURRENTCLASS.yVel = 0;}
			if (CURRENTCLASS.xPos < 500) {CURRENTCLASS.xPos = 500; CURRENTCLASS.xVel = x;}
			else if (CURRENTCLASS.xPos + 49 > 5500) {CURRENTCLASS.xPos = 5500 - 49; CURRENTCLASS.xVel = 0;}
			if(CURRENTCLASS.Active == 1)
			{
				if(Ded == false)
				{
					if (PlayerX > CURRENTCLASS.xPos && PlayerX < CURRENTCLASS.xPos + 49 && PlayerY > CURRENTCLASS.yPos && PlayerY < CURRENTCLASS.yPos + 25) 	
					{
						Lives--;
						if (Lives == -1)
						{
							Ded = true;
							KillerID = CURRENTCLASS.ID;
						}
					}
					else if (PlayerX + 27 > CURRENTCLASS.xPos && PlayerX + 27 < CURRENTCLASS.xPos + 49 && PlayerY + 25 > CURRENTCLASS.yPos && PlayerY + 25 < CURRENTCLASS.yPos + 25) 	
					{
						Lives--;
						if (Lives == -1)
						{
							Ded = true;
							KillerID = CURRENTCLASS.ID;
						}
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
									Kills++;
								}

								else if (XPOS + 11 > CURRENTCLASS.xPos && XPOS + 11 < CURRENTCLASS.xPos + 25 && YPOS + 11 > CURRENTCLASS.yPos && YPOS+11 < CURRENTCLASS.yPos + 49)
								{
									CURRENTCLASS.Active = 0;
									ACTIVE = 0;
									Kills++;
								}
							}
						}
					}

					double DeltaX, DeltaY;
					double Distance;
					
					if (CURRENTCLASS.xPos > PlayerX - 10 && CURRENTCLASS.xPos < PlayerX + 10)
					{
						if (CURRENTCLASS.yPos > PlayerY) CURRENTCLASS.yVel--;
						else CURRENTCLASS.yVel++;
					}

					else if (PlayerX < CURRENTCLASS.xPos &&  PlayerY < CURRENTCLASS.yPos) //Top left
					{
						int poo = CURRENTCLASS.xPos;
						int wee = CURRENTCLASS.yPos;

						DeltaX = CURRENTCLASS.xPos - PlayerX;
						DeltaY = CURRENTCLASS.yPos - PlayerY;
						Distance = sqrt(DeltaX + DeltaY);
						CURRENTCLASS.xVel = (DeltaX / Distance) * -1;
						CURRENTCLASS.yVel = DeltaY / Distance;//) * -1;
						int anus = CURRENTCLASS.yVel;
					}

					else if (PlayerX > CURRENTCLASS.xPos &&  PlayerY < CURRENTCLASS.yPos) //Top right
					{
						DeltaX = PlayerX - CURRENTCLASS.xPos;
						DeltaY = CURRENTCLASS.yPos - PlayerY;
						Distance = sqrt(DeltaX + DeltaY);
						CURRENTCLASS.xVel = DeltaX / Distance;
						CURRENTCLASS.yVel = DeltaY / Distance;
					}
	
					else if (PlayerX < CURRENTCLASS.xPos &&  PlayerY > CURRENTCLASS.yPos) //Bottom left
					{
						DeltaX = CURRENTCLASS.xPos - PlayerX;
						DeltaY = PlayerY - CURRENTCLASS.yPos;
						Distance = sqrt(DeltaX + DeltaY);
						CURRENTCLASS.xVel = (DeltaX / Distance) * -1;
						CURRENTCLASS.yVel = (DeltaY / Distance) * -1;
					}
	
					else if (PlayerX > CURRENTCLASS.xPos &&  PlayerY > CURRENTCLASS.yPos) //Bottom right
					{
						DeltaX = PlayerX - CURRENTCLASS.xPos;
						DeltaY = PlayerY - CURRENTCLASS.yPos;
						Distance = sqrt(DeltaX + DeltaY);
						CURRENTCLASS.xVel = DeltaX / Distance;
						CURRENTCLASS.yVel = DeltaY / Distance;
					}
					CURRENTCLASS.yVel = (CURRENTCLASS.yVel * -1) / 2;
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

				if (CURRENTCLASS.xPos + 49 > CameraX && CURRENTCLASS.xPos  < CameraX + 800 && CURRENTCLASS.yPos > CameraY && CURRENTCLASS.yPos < CameraY + 500)
				{
					if (CURRENTCLASS.Facing == 1) ApplySurface(CURRENTCLASS.xPos - CameraX, CURRENTCLASS.yPos - CameraY,EnemyDownClips,Screen,&EnemyDownClipRect[CURRENTCLASS.Frame]);
					else ApplySurface(CURRENTCLASS.xPos - CameraX, CURRENTCLASS.yPos - CameraY,EnemyUpClips,Screen,&EnemyDownClipRect[CURRENTCLASS.Frame]);
				}
				else if (Ded == false)
				{
					if(CURRENTCLASS.xPos + 49 < CameraX && CURRENTCLASS.yPos < CameraY) ApplySurface(0,0,EnemuIndicator,Screen);
					else if (CURRENTCLASS.xPos + 49 < CameraX && CURRENTCLASS.yPos > CameraY + ScreenHeight) ApplySurface(0,ScreenHeight - EnemuIndicator->h,EnemuIndicator,Screen);
					else if (CURRENTCLASS.xPos + 49 > CameraX + ScreenHeight && CURRENTCLASS.yPos < CameraY) ApplySurface(ScreenWidth - EnemuIndicator->h,0,EnemuIndicator,Screen);
					else if (CURRENTCLASS.xPos + 49 > CameraX + ScreenHeight && CURRENTCLASS.yPos > CameraY + ScreenHeight) ApplySurface(ScreenWidth - EnemuIndicator->h,ScreenHeight - EnemuIndicator->h,EnemuIndicator,Screen);
					else if (CURRENTCLASS.xPos + 49 < CameraX) ApplySurface(0,CURRENTCLASS.yPos - CameraY,EnemuIndicator,Screen);
					else if (CURRENTCLASS.xPos > CameraX + ScreenWidth) ApplySurface(ScreenWidth - EnemuIndicator->w, CURRENTCLASS.yPos - CameraY,EnemuIndicator,Screen);
					else if (CURRENTCLASS.yPos > CameraY + ScreenHeight) ApplySurface(CURRENTCLASS.xPos - CameraX,ScreenHeight - EnemuIndicator->h,EnemuIndicator,Screen);
					else if (CURRENTCLASS.yPos < CameraY) ApplySurface(CURRENTCLASS.xPos - CameraX,0,EnemuIndicator,Screen);
				}
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