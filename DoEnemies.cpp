#include"DoEnemies.h"
#include"Declarations.h"
#include"Game.h"

void CheckShake();
int InvincibilityFrames = 0;



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
	InvincibilityFrames++;
	if (EnemyVector.size() >= 1)
	{
		for(int x = 0; x < EnemyVector.size(); x++)
		{
			if (CURRENTCLASS.yPos < 500) {CURRENTCLASS.yPos = 500; CURRENTCLASS.yVel = CURRENTCLASS.yVel / -2;}
			else if (CURRENTCLASS.yPos + 25 > 5500) {CURRENTCLASS.yPos = 5500 - 25; CURRENTCLASS.yVel = CURRENTCLASS.yVel / -2;}
			if (CURRENTCLASS.xPos < 500) {CURRENTCLASS.xPos = 500; CURRENTCLASS.xVel = CURRENTCLASS.xVel / -2;}
			else if (CURRENTCLASS.xPos + 49 > 5500) {CURRENTCLASS.xPos = 5500 - 49; CURRENTCLASS.xVel = CURRENTCLASS.xVel / -2;}
			if(CURRENTCLASS.Active == 1)
			{
				if(Ded == false)
				{
					if (InvincibilityFrames > 120)
					{
						if (PlayerX >= CURRENTCLASS.xPos && PlayerX <= CURRENTCLASS.xPos + 49 && PlayerY >= CURRENTCLASS.yPos && PlayerY <= CURRENTCLASS.yPos + 25) 	
						{
							Lives--;
							InvincibilityFrames = 0;
							Dur = 30; Mag = 14;
							if (Lives == -1)
							{
								Ded = true;
								LDown,RDown,UDown,DDown = false;
								KillerID = CURRENTCLASS.ID;
							}
						}
						else if (PlayerX + 27 > CURRENTCLASS.xPos && PlayerX + 27 < CURRENTCLASS.xPos + 49 && PlayerY + 25 > CURRENTCLASS.yPos && PlayerY + 25 < CURRENTCLASS.yPos + 25) 	
						{
							Lives--;
							InvincibilityFrames = 0;
							Dur = 30; Mag = 14;
							if (Lives == -1)
							{
								Ded = true;
								LDown,RDown,UDown,DDown = false;
								KillerID = CURRENTCLASS.ID;
							}
						}
						else if (PlayerX + 27 > CURRENTCLASS.xPos && PlayerX + 27 < CURRENTCLASS.xPos + 49 && PlayerY > CURRENTCLASS.yPos && PlayerY < CURRENTCLASS.yPos + 25) 	
						{
							Lives--;
							InvincibilityFrames = 0;
							Dur = 30; Mag = 14;
							if (Lives == -1)
							{
								Ded = true;
								LDown,RDown,UDown,DDown = false;
								KillerID = CURRENTCLASS.ID;
							}
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

					int PseudoX = PlayerX + Character.xVel * CURRENTCLASS.Random;
					int PseudoY = PlayerY + Character.yVel * CURRENTCLASS.Random;
					
					if (PseudoX < CURRENTCLASS.xPos &&  PseudoY < CURRENTCLASS.yPos) //Top left
					{
						DeltaX = CURRENTCLASS.xPos - PseudoX;
						DeltaY = CURRENTCLASS.yPos - PseudoY;
						Distance = sqrt(DeltaX + DeltaY);
						CURRENTCLASS.xVel = (DeltaX / Distance) * -1;
						CURRENTCLASS.yVel = DeltaY / Distance;//) * -1;
						CURRENTCLASS.Facing = 0;
					}

					else if (PseudoX > CURRENTCLASS.xPos &&  PseudoY < CURRENTCLASS.yPos) //Top right
					{
						DeltaX = PseudoX - CURRENTCLASS.xPos;
						DeltaY = CURRENTCLASS.yPos - PseudoY;
						Distance = sqrt(DeltaX + DeltaY);
						CURRENTCLASS.xVel = DeltaX / Distance;
						CURRENTCLASS.yVel = DeltaY / Distance;
						CURRENTCLASS.Facing = 0;
					}
	
					else if (PseudoX < CURRENTCLASS.xPos &&  PseudoY > CURRENTCLASS.yPos) //Bottom left
					{
						DeltaX = CURRENTCLASS.xPos - PseudoX;
						DeltaY = PseudoY - CURRENTCLASS.yPos;
						Distance = sqrt(DeltaX + DeltaY);
						CURRENTCLASS.xVel = (DeltaX / Distance) * -1;
						CURRENTCLASS.yVel = (DeltaY / Distance) * -1;
						CURRENTCLASS.Facing = 1;
					}
	
					else if (PseudoX > CURRENTCLASS.xPos &&  PseudoY > CURRENTCLASS.yPos) //Bottom right
					{
						DeltaX = PseudoX - CURRENTCLASS.xPos;
						DeltaY = PseudoY - CURRENTCLASS.yPos;
						Distance = sqrt(DeltaX + DeltaY);
						CURRENTCLASS.xVel = DeltaX / Distance;
						CURRENTCLASS.yVel = (DeltaY * -1) / Distance;
						CURRENTCLASS.Facing = 1;
					}
					else
					{
						if (CURRENTCLASS.xPos == PlayerX) CURRENTCLASS.xPos++;
						else if (CURRENTCLASS.yPos == PlayerY) CURRENTCLASS.yPos--;
					}
					CURRENTCLASS.yVel = CURRENTCLASS.yVel * -1;
					//CURRENTCLASS.xVel = CURRENTCLASS.xVel * 1.5;
					//PlayerX = Character.WorldxPos;
					//PlayerY = Character.WorldyPos;

				}

				else
				{
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

				CURRENTCLASS.xPos += CURRENTCLASS.xVel;
				CURRENTCLASS.yPos += CURRENTCLASS.yVel;
				CURRENTCLASS.FrameTime++;
				if(CURRENTCLASS.FrameTime == 10)
				{
					CURRENTCLASS.FrameTime = 0;
					CURRENTCLASS.Frame++;
					if (CURRENTCLASS.Frame == 7) CURRENTCLASS.Frame = 0;
				}

				if (CURRENTCLASS.Frame > 3) CURRENTCLASS.yPos += 3;

				if (CURRENTCLASS.xPos + 49 > CameraX && CURRENTCLASS.xPos  < CameraX + 800 && CURRENTCLASS.yPos + 49 > CameraY && CURRENTCLASS.yPos < CameraY + 500)
				{
					if (CURRENTCLASS.Facing == 1) ApplySurface(CURRENTCLASS.xPos - CameraX, CURRENTCLASS.yPos - CameraY,EnemyDownClips,Screen,&EnemyDownClipRect[CURRENTCLASS.Frame]);
					else ApplySurface(CURRENTCLASS.xPos - CameraX, CURRENTCLASS.yPos - CameraY,EnemyUpClips,Screen,&EnemyDownClipRect[CURRENTCLASS.Frame]);
				}
				else if (Ded == false)
				{
					if(CURRENTCLASS.xPos + 49 < CameraX && CURRENTCLASS.yPos < CameraY) ApplySurface(0,0,EnemuIndicator,Screen,&IndicatorClips[7]); //Top left
					else if (CURRENTCLASS.xPos + 49 < CameraX && CURRENTCLASS.yPos > CameraY + ScreenHeight) ApplySurface(0,ScreenHeight - 50,EnemuIndicator,Screen,&IndicatorClips[5]); //Bottom left
					else if (CURRENTCLASS.xPos + 49 > CameraX + ScreenWidth && CURRENTCLASS.yPos < CameraY) ApplySurface(ScreenWidth - 50,0,EnemuIndicator,Screen,&IndicatorClips[1]); //Top right
					else if (CURRENTCLASS.xPos + 49 > CameraX + ScreenWidth && CURRENTCLASS.yPos > CameraY + ScreenHeight) ApplySurface(ScreenWidth - 50,ScreenHeight - 50,EnemuIndicator,Screen,&IndicatorClips[3]); //Bottom right
					else if (CURRENTCLASS.xPos + 49 < CameraX) ApplySurface(0,CURRENTCLASS.yPos - CameraY,EnemuIndicator,Screen,&IndicatorClips[6]); //Left
					else if (CURRENTCLASS.xPos > CameraX + ScreenWidth) ApplySurface(ScreenWidth - 50, CURRENTCLASS.yPos - CameraY,EnemuIndicator,Screen,&IndicatorClips[2]); //Right
					else if (CURRENTCLASS.yPos > CameraY + ScreenHeight) ApplySurface(CURRENTCLASS.xPos - CameraX,ScreenHeight - 50,EnemuIndicator,Screen,&IndicatorClips[4]); //Bottom
					else if (CURRENTCLASS.yPos < CameraY) ApplySurface(CURRENTCLASS.xPos - CameraX,0,EnemuIndicator,Screen,&IndicatorClips[0]); //Top
				}
				if (CURRENTCLASS.Frame > 3) CURRENTCLASS.yPos -= 3;
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

void CheckShake()
{
	if (InvincibilityFrames > 10 && InvincibilityFrames < 20) ShallIRenderHim = false;
	else if (InvincibilityFrames > 30 && InvincibilityFrames < 40) ShallIRenderHim = false;
	else if (InvincibilityFrames > 50 && InvincibilityFrames < 60) ShallIRenderHim = false;
	else if (InvincibilityFrames > 70 && InvincibilityFrames < 80) ShallIRenderHim = false;
	else if (InvincibilityFrames > 90 && InvincibilityFrames < 100) ShallIRenderHim = false;
	else if (InvincibilityFrames > 110 && InvincibilityFrames < 120) ShallIRenderHim = false;
	else ShallIRenderHim = true; 

	if (Dur >= 1)
	{
		Dur--;
		Viewport.xOffSet = rand () % Mag + ((Mag/2)* -1);
		Viewport.yOffSet = rand () % Mag + ((Mag/2) * -1);
		if (Dur == 1)
		{
			XChange = 0;
			YChange = 0;
		}
	}
}

void CreateEnemy()
{
	Enemy TopLel;
	EnemyVector.push_back(TopLel);
}