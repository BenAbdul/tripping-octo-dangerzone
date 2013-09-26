#include"DoEnemies.h"
#include"Declarations.h"

Enemy::Enemy()
{
	if(CameraX > 2500) xPos = CameraX;
	else xPos = CameraX + 10;

	if(CameraY > 2500) yPos = CameraY;
	else yPos = CameraY + 10;

	xVel = 0;
	yVel = 0;
	Active = 1;
}

std::vector<Enemy> EnemyVector;


#define CURRENTCLASS EnemyVector.at(x)
void DoEnemies()
{
	if(EnemyVector.size() > 1)
	{
		for(int x = 0; x < EnemyVector.size(); x++)
		{
			if(CURRENTCLASS.xPos > PlayerX && CURRENTCLASS.xVel >= -5) CURRENTCLASS.xVel--;
			else if (CURRENTCLASS.xPos < PlayerX && CURRENTCLASS.xVel <= 5) CURRENTCLASS.xVel++;
			
			if(CURRENTCLASS.yPos > PlayerY && CURRENTCLASS.yVel >= -5) CURRENTCLASS.yVel--;
			else if (CURRENTCLASS.yPos < PlayerY && CURRENTCLASS.yVel <= 5) CURRENTCLASS.yVel++;

			CURRENTCLASS.xPos += CURRENTCLASS.xVel;
			CURRENTCLASS.yPos += CURRENTCLASS.yVel;

			ApplySurface(CameraX - CURRENTCLASS.xPos,CameraY - CURRENTCLASS.yPos, EnemyClips, Screen);
		}
	}
}
void CreateEnemy()
{
	Enemy TopLel;
	EnemyVector.push_back(TopLel);
}