#include"DoEnemies.h"
#include"Declarations.h"

Enemy::Enemy()
{
	if(CameraX > 2500) xPos = CameraX - 10;
	else xPos = CameraX + 10;

	if(CameraY > 2500) yPos = CameraY;
	else yPos = CameraY + 10;
	Frame = 0;
	FrameTime = 0;
	xVel = 0;
	yVel = 0;
	Active = 1;
}

std::vector<Enemy> EnemyVector;


#define CURRENTCLASS EnemyVector.at(x)
//Enemy clip size 49x36
//Collision size 49x25
void DoEnemies()
{
	if(EnemyVector.size() >= 1)
	{
		for(int x = 0; x < EnemyVector.size(); x++)
		{
			if (CURRENTCLASS.xPos > PlayerX && CURRENTCLASS.xVel >= -1) CURRENTCLASS.xVel--;
			else if (CURRENTCLASS.xPos < PlayerX && CURRENTCLASS.xVel <= 1) CURRENTCLASS.xVel++;
			if (CURRENTCLASS.yPos > PlayerY && CURRENTCLASS.yVel >=-1) CURRENTCLASS.yVel--;
			else if (CURRENTCLASS.yPos < PlayerY && CURRENTCLASS.yVel <= 1) CURRENTCLASS.yVel++;
			CURRENTCLASS.xPos += CURRENTCLASS.xVel;
			CURRENTCLASS.yPos += CURRENTCLASS.yVel;
			CURRENTCLASS.FrameTime++;
			if(CURRENTCLASS.FrameTime == 10)
			{
				CURRENTCLASS.FrameTime = 0;
				CURRENTCLASS.Frame++;
				if (CURRENTCLASS.Frame == 7) CURRENTCLASS.Frame = 0;
			}
			ApplySurface(CURRENTCLASS.xPos - CameraX, CURRENTCLASS.yPos - CameraY,EnemyDownClips,Screen,&EnemyDownClipRect[CURRENTCLASS.Frame]);
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